solution "gKit2light"
	configurations { "debug", "release" }

	platforms { "x64", "x32" }
	
	includedirs { ".", "src/gKit" }
	
	gkit_dir = path.getabsolute(".")
	
	
	configuration "debug"
		targetdir "bin/debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "release"
		targetdir "bin/release"
--~ 		defines { "NDEBUG" }
--~ 		defines { "GK_RELEASE" }
		flags { "OptimizeSpeed" }

	configuration "linux"
		buildoptions { "-mtune=native -march=native" }
		buildoptions { "-std=c++11" }
		buildoptions { "-W -Wall -Wextra -Wsign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable", "-pipe" }
		buildoptions { "-flto"}
		linkoptions { "-flto"}
		links { "GLEW", "SDL2", "SDL2_image", "GL" }

	configuration { "linux", "debug" }
		buildoptions { "-g"}
		linkoptions { "-g"}
		
	configuration { "linux", "release" }
		buildoptions { "-fopenmp" }
		linkoptions { "-fopenmp" }

	configuration { "windows" }
		defines { "WIN32", "NVWIDGETS_EXPORTS", "_USE_MATH_DEFINES", "_CRT_SECURE_NO_WARNINGS" }
		defines { "NOMINMAX" } -- allow std::min() and std::max() in vc++ :(((

	configuration { "windows", "gmake", "x32" }
		buildoptions { "-std=c++11"}
		includedirs { "extern/mingw/include" }
		libdirs { "extern/mingw/lib" }
		links { "mingw32", "SDL2main", "SDL2", "SDL2_image", "opengl32", "glew32" }

	configuration { "windows", "codeblocks", "x32" }
		buildoptions { "-std=c++11"}
		includedirs { "extern/mingw/include" }
		libdirs { "extern/mingw/lib" }
		links { "mingw32", "SDL2main", "SDL2", "SDL2_image", "opengl32", "glew32" }
		
	configuration { "windows", "vs2013" }
		if _PREMAKE_VERSION >="5.0" then
			system "Windows"
			architecture "x64"
			disablewarnings { "4244", "4305" }
		end
		includedirs { "extern/visual2013/include" }
		libdirs { "extern/visual2013/lib" }
		platforms { "x64" }
		links { "opengl32", "glew32", "SDL2", "SDL2main", "SDL2_image" }

		
	configuration { "windows", "vs2015" }
		if _PREMAKE_VERSION >="5.0" then
			system "Windows"
			architecture "x64"
			disablewarnings { "4244", "4305" }
			flags { "MultiProcessorCompile", "NoMinimalRebuild" }
		end
		includedirs { "extern/visual2015/include" }
		libdirs { "extern/visual2015/lib" }
		links { "opengl32", "glew32", "SDL2", "SDL2main", "SDL2_image" }
		
	configuration { "windows", "vs2017" }
		if _PREMAKE_VERSION >="5.0" then
			system "Windows"
			architecture "x64"
			disablewarnings { "4244", "4305" }
			flags { "MultiProcessorCompile", "NoMinimalRebuild" }
		end

		-- memes librairies que pour la version 2015
		includedirs { "extern/visual2015/include" }
		libdirs { "extern/visual2015/lib" }
		links { "opengl32", "glew32", "SDL2", "SDL2main", "SDL2_image" }
		
	configuration "macosx"
		frameworks= "-F /Library/Frameworks/"
		buildoptions { "-std=c++11" }
		defines { "GK_MACOS" }
		buildoptions { frameworks }
		linkoptions { frameworks .. " -framework OpenGL -framework SDL2 -framework SDL2_image" }


 -- description des fichiers communs
gkit_files = { gkit_dir .. "/src/gKit/*.cpp", gkit_dir .. "/src/gKit/*.h" }


-- quand ce premake4.lua est inclus par un autre premake qui definit no_project=true (donc quand gkit2light est utilisé comme une lib),
-- ceci stoppe la creation des projects suivants (tuto, etc.)
if no_project then
	do return end
end

 -- description des projets		 
projects = {
	"shader_kit",
	"image_viewer"
}

for i, name in ipairs(projects) do
	project(name)
		language "C++"
		kind "ConsoleApp"
		targetdir "bin"
		files ( gkit_files )
		files { gkit_dir .. "/src/" .. name..'.cpp' }
end

 -- description des tutos
tutos = {
	"tuto1",
	"tuto2",
	"tuto3",
	"tuto4",
	"tuto5",
	"tuto6",
	"tuto7",
	"tuto8",
	"tuto9",
	"tuto9_texture1",
	"tuto9_textures",
	
	"tuto_transform",
	"tuto_pad",
	
	"tuto1GL",
	"tuto2GL",
	"tuto2GL_app",
	"tuto3GL",
	"tuto3GL_reflect",
	"tuto4GL",
	"tuto4GL_normals",
	"tuto5GL",
	"tuto5GL_sampler",
	"tuto5GL_samplers",
	"tuto5GL_multi",
	"tuto6GL",
	"tuto6GL_buffer",
	"mesh_viewer_sort",
	"tuto_framebuffer",
	"tuto_storage",
	"tuto_storage_buffer",
	"tuto_storage_texture",
	"min_data"
}

for i, name in ipairs(tutos) do
	project(name)
		language "C++"
		kind "ConsoleApp"
		targetdir "bin"
		files ( gkit_files )
		files { gkit_dir .. "/tutos/" .. name..'.cpp' }
end

project("mesh_viewer")
	language "C++"
	kind "ConsoleApp"
	targetdir "bin"
	files ( gkit_files )
	files { gkit_dir .. "/tutos/mesh_viewer.cpp"}
	files { gkit_dir .. "/tutos/mesh_buffer.cpp"}
	files { gkit_dir .. "/tutos/mesh_buffer.h"}
	files { gkit_dir .. "/tutos/mesh_data.cpp"}
	files { gkit_dir .. "/tutos/mesh_data.h"}
	files { gkit_dir .. "/tutos/material_data.cpp"}
	files { gkit_dir .. "/tutos/material_data.h"}


-- description des tutos openGL avances / M2
tutosM2 = {
	"tuto_time",
	"tuto_mdi",
	"tuto_is",
	"tuto_raytrace_fragment"
}

for i, name in ipairs(tutosM2) do
	project(name)
		language "C++"
		kind "ConsoleApp"
		targetdir "bin"
		files ( gkit_files )
		files { gkit_dir .. "/tutos/M2/" .. name..'.cpp' }
end
