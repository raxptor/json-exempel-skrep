solution "Dundje"

    location "build"
    targetdir "build"

    defines {"_CRT_SECURE_NO_WARNINGS"}
	
    configurations {"Debug"}
	configuration "Debug"
		flags { "Symbols" }
	
    dofile "putki/libs.lua"
    
    project "dundje"
        language "C++"
        kind "ConsoleApp"
        targetname "dundje-putki-lib"
        putki_use_builder_lib()
        putki_typedefs_builder("src/types", true)
		files "src/main.cpp"

