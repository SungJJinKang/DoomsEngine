# Dooms Engine ( Game Engine ) ( 2021.01.07 ~ )
  
## Video

[Game Engine Video](https://youtube.com/playlist?list=PLUg9a0kyCgTR3OhYZYSMauDmjv6D96pVz)              

## Features

  * C++17
  * C# ( used for making engine tools )    
  * Target Compiler : MSVC ( clang is used for generating reflection data )
  * Supported Graphics API : OpenGL, DIRECTX 11 ( 80% )
  * Component based System
  * Deferred Rendering ( [video](https://youtu.be/TU9P8gcKsi8) )
  * Homemade Math Library ( [source code](https://github.com/SungJJinKang/LightMath_Cpp) )     
  * Multi Thread ViewFrustum Culling From FrostBite Engine of EA Dice ( [source code](https://github.com/SungJJinKang/EveryCulling/tree/main/CullingModule/ViewFrustumCulling), [개발 일지](https://sungjjinkang.github.io/doom/c++/computergraphics/game/2021/04/02/viewfrustumculling.html) )
  * Support SIMD ( Currently AVX2 )
  * Asset Import Pipeline ( Automatically import assets located in asset folder )
  * JobSystem ( [source code](https://github.com/SungJJinKang/JobSystem_cpp) )
  * Collision, Raycasting, Picking ( implemented with BVH Tree ) ( [video](https://youtu.be/ZASdCIKeG6s) )
  * BVH, KDTree ( [bvh source code](https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/utility/BVH), [kdtree source code](https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/utility/KDTree) )                          
  * Object Management System for preventing memory leak ( [개발 일지](https://sungjjinkang.github.io/computerscience/gameengine/2021/09/25/dangling_pointer.html) )
  * Fast Runtime Type Casting ( writing manually type name is not required, reflection data is used. check reflection.h files ) ( time complexicity is always O(1), dynamic_cast isn't used ( RTTI option is disabled ), [source code](https://github.com/SungJJinKang/Fast_Runtime_TypeCasting_cpp) )        
  * Automatic Reflection Data Generation System. ( [video](https://youtu.be/KGihaYTzqG8) ) ( [clrefelct_automation](https://github.com/SungJJinKang/clReflect_automation) )
  * Customizing Reflection Open Source Library ( [video](https://youtu.be/9DKGvkdR6zw) ) ( [Customized clReflect](https://github.com/SungJJinKang/clReflect_ForDoomsEngine) )
  * Integrate imgui with reflection system. ( DObjects, std::vector, std::array, std::unique_ptr... is supported, [video](https://youtu.be/wxZIGoTRcpo) )
  * Garbage Collector using reflection system ( stop-the-world, Mark ( multithread ) - Sweep algorithm, std::array, std::vector is also supported, nullify pointer referencing destroyed object ( to prvent referencing invalid address ), [개발 일지](https://sungjjinkang.github.io/computerscience/2021/12/01/reflection_gc.html), [video](https://youtu.be/E4CNOIXYQnQ), [soure code](https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/GarbageCollector) )
  * Masked SW ( CPU ) Occlusion Culling From Intel ( [video1](https://youtu.be/tMgokVljvAY), [video2](https://youtu.be/1IKTXsSLJ5g), [source code](https://github.com/SungJJinKang/EveryCulling/tree/main/CullingModule/MaskedSWOcclusionCulling), [개발 일지](https://sungjjinkang.github.io/computerscience/computergraphics/2021/12/31/masked_sw_occlusion_culling.html), [reference paper](https://software.intel.com/content/dam/develop/external/us/en/documents/masked-software-occlusion-culling.pdf] )        
  * Distance Culling from Unreal Engine ( [reference](https://docs.unrealengine.com/en-US/RenderingAndGraphics/VisibilityCulling/CullDistanceVolume/index.html), [soure code](https://github.com/SungJJinKang/EveryCulling/tree/main/CullingModule/DistanceCulling) )      
  * Shader Language Portable System ( Automatically convert glsl files to hlsl, [glslcc](https://github.com/septag/glslcc) is used )     
  * Shader Reflection System ( Provide shader variables data ( size, offset, variable name ... ) )    
  
## Currently working on     
   
  * implement D3D11
  * Refactory engine architect ( like [this](https://4.bp.blogspot.com/-E5Np_k78ZH4/WNfg2zjEPnI/AAAAAAAAJ0I/MQlvchgGlRQRsC46Nhmrfbaj4mSerE1MQCLcB/s1600/Screen%2BShot%2B2017-03-26%2Bat%2B9.39.44%2BAM.png) )           
   
## To Develop
       
  * implement physical based rendering ( https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf )  
  * implement Hierarchical Shadow map
  * Batch Rendering
                 
## Thirdparty Dependencies            
             
  * [glfw](https://github.com/glfw/glfw) : A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input                     
  * [assimp](https://github.com/assimp/assimp) : The official Open-Asset-Importer-Library Repository                    
  * [DirectTex](https://github.com/microsoft/DirectXTex) : DirectXTex texture processing library       
  * [imgui](https://github.com/ocornut/imgui) : Dear ImGui: Bloat-free Graphical User interface for C++ with minimal dependencies        
  * [Intel TBB ( malloc proxy )](https://github.com/oneapi-src/oneTBB)          
  * [concurrentqueue](https://github.com/cameron314/concurrentqueue) : A fast multi-producer, multi-consumer lock-free concurrent queue for C++11                       
  * [json](https://github.com/nlohmann/json) : JSON for Modern C++             
  * [glslcc](https://github.com/septag/glslcc) : GLSL cross-compiler tool (GLSL->HLSL, MSL, GLES2, GLES3, GLSLv3), using SPIRV-cross and glslang                   
  * [magic_enum](https://github.com/Neargye/magic_enum) : Static reflection for enums (to string, from string, iteration) for modern C++                 
 
## Screenshot
![20220123003649](https://user-images.githubusercontent.com/33873804/150645275-f773d8d6-2b38-4f51-9d00-9692fa1aa57c.png)                
![20220123003708](https://user-images.githubusercontent.com/33873804/150645279-202f313a-9574-40ea-a138-c24693529d1c.png)                

## Coding Standard

[English](https://docs.google.com/document/d/1cT8EPgMXe0eopeHvwuFmbHG4TJr5kUmcovkr5irQZmo/edit)   
[Korean](https://docs.popekim.com/ko/coding-standards/cpp)


## Development Blog

[Korean Blog](https://sungjjinkang.github.io/) 
