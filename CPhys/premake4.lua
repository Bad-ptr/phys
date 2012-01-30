-- A solution contains projects, and defines the available configurations
solution "PhysicalApps"
    configurations { "Debug", "Release" }

-- A project defines one build target
    project "PhysTryOnC"
        kind "ConsoleApp"
        language "C"
        defines {CC="clang"}
        links {"c", "m", "GL", "GLU", "glut", "pthread", "gomp"}
        files { "src/**.h", "src/**.c" }

        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }    
