#include <iostream>
#include <fstream>

#include <putki/builder/parse.h>
#include <putki/builder/write.h>
#include <putki/sys/sstream.h>

#include "inki/types/Stuff.h"


template<typename InkiType>
bool load_from_buffer(InkiType* out, char *json, int size)
{
	json[size] = 0;
	std::cout << json << std::endl;
	putki::parse::data* pd = putki::parse::parse_json(json, size);
	if (!pd)
	{
		std::cerr << "Failed to parse json!" << std::endl;
		return false;
	}

	struct no_resolve : putki::load_resolver_i
	{
		void resolve_pointer(putki::instance_t *ptr, const char *path)
		{
			*ptr = 0;
		}
	};

	no_resolve res;	
	InkiType::th()->fill_from_parsed(putki::parse::get_root(pd), out, &res);
	putki::parse::free(pd);
	return true;
}

int main()
{
	inki::window moeg;

	char buf[65536];
	FILE *f = fopen("data/window.json", "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	fread(buf, fsize, 1, f);
	fclose(f);

	// read
	if (!load_from_buffer(&moeg, buf, (int)fsize))
	{		
		std::cout << "No json no cry";
		return 1;
	}
	
	std::cout << "Window " << moeg.width << "x" << moeg.height << " with " << moeg.panes.size() << " panes" << std::endl;
	for (size_t i=0;i!=moeg.panes.size();i++)
	{
		std::cout << "pane[" << i << "] = " << moeg.panes[i].left << " " << moeg.panes[i].top << " " << moeg.panes[i].right << " " << moeg.panes[i].bottom << " type=" << moeg.panes[i].type << "  (" << pane_type_to_string(moeg.panes[i].type) << ")" << std::endl;
	}

	// write
	inki::window korv;
	korv.title = "Bengt";
	korv.height = 100000;

	putki::sstream tmp;	
	std::cout << "Writing..." << std::endl;

	std::cout << "{" << std::endl;
	inki::window::th()->write_json(0, &korv, tmp, 0);
	std::cout << tmp.c_str() << std::endl;
	std::cout << "}" << std::endl;
	


	return 0;
}