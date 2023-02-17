# Dooms Engine ( Game Engine ) ( 2021.01 ~ 2022.03 )
  
## Video

[Game Engine Video](https://youtube.com/playlist?list=PLUg9a0kyCgTR3OhYZYSMauDmjv6D96pVz)              

## Features

### Requirement

  * C++17
  * C# ( used for making engine tools )    
  * Windows, x64, VisualStudio 2022(vc17)
  * Target Compiler : MSVC, Clang ( clang is used for [generating reflection data](https://github.com/SungJJinKang/clReflect_ForDoomsEngine) )

### Engine Core

  * Homemade Math Library ( [JINMATH](https://github.com/SungJJinKang/JINMATH) )      
  * Support SIMD ( Currently AVX2 ) ( Math, Culling.... )           
  * Asset Import Pipeline ( Automatically import assets located in asset folder )
  * Component based System
  * Object Management System for preventing memory leak ( [개발 일지](https://sungjjinkang.github.io/dangling_pointer.html) )
  * Fast Runtime Type Casting ( writing manually type name is not required, reflection data is used. check reflection.h files ) ( time complexicity is always O(1), dynamic_cast isn't used ( RTTI option is disabled ), [source code](https://github.com/SungJJinKang/Fast_Runtime_TypeCasting_cpp) )        
  * Garbage Collector using reflection system ( stop-the-world, Mark ( multithread ) - Sweep algorithm, std::array, std::vector is also supported, nullify pointer referencing destroyed object ( to prvent referencing invalid address ), [개발 일지](https://sungjjinkang.github.io/reflection_gc.html), [video](https://youtu.be/E4CNOIXYQnQ), [soure code](https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/GarbageCollector) )
  
### Rendering

  * OpenGL, DIRECTX 11(Partially)
  * Deferred Rendering ( [video](https://youtu.be/TU9P8gcKsi8) )
  * Sort objects from front to back
  * Multi Thread ViewFrustum Culling From FrostBite Engine of EA Dice ( [source code](https://github.com/SungJJinKang/EveryCulling/tree/main/CullingModule/ViewFrustumCulling), [개발 일지](https://sungjjinkang.github.io/viewfrustumculling.html) )
  * Masked SW ( CPU ) Occlusion Culling From Intel ( [video1](https://youtu.be/tMgokVljvAY), [video2](https://youtu.be/1IKTXsSLJ5g), [source code](https://github.com/SungJJinKang/EveryCulling/tree/main/CullingModule/MaskedSWOcclusionCulling), [개발 일지](https://sungjjinkang.github.io/masked_sw_occlusion_culling.html), [reference paper](https://software.intel.com/content/dam/develop/external/us/en/documents/masked-software-occlusion-culling.pdf] )        
  * Distance Culling from Unreal Engine ( [reference](https://docs.unrealengine.com/en-US/RenderingAndGraphics/VisibilityCulling/CullDistanceVolume/index.html), [soure code](https://github.com/SungJJinKang/EveryCulling/tree/main/CullingModule/DistanceCulling) )      
  * Shader Language Portable System ( Automatically convert glsl files to hlsl, [glslcc](https://github.com/septag/glslcc) is used )     
  * Shader Reflection System ( Provide shader variables data ( size, offset, variable name ... ) )    
  * Static Batch Rendering ( [video](https://youtu.be/bBDbO7hS12g), Mesh data of static objects with same material is combined automatically at start of scene. They are drawed in 1 draw call )              

### Physics

  * Collision, Raycasting, Picking ( implemented with BVH Tree ) ( [Picking Test Video](https://youtu.be/ZASdCIKeG6s), [Collision Test Video](https://youtu.be/s--m0QcmYYw) )                 
  * BVH, KDTree ( [bvh source code](https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/Misc/AccelerationContainer/BVH), [kdtree source code](https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/Misc/AccelerationContainer/KDTree) )        

### Reflection    
  
  * Automatic Reflection Data Generation System. ( [video](https://youtu.be/KGihaYTzqG8) ) ( [clrefelct_automation](https://github.com/SungJJinKang/clReflect_automation) )
  * Customized Reflection Open Source Library ( [video](https://youtu.be/9DKGvkdR6zw) ) ( [Customized clReflect](https://github.com/SungJJinKang/clReflect_ForDoomsEngine) )
  * Integrate imgui with reflection system. ( DObjects, std::vector, std::array, std::unique_ptr... is supported, [video](https://youtu.be/wxZIGoTRcpo) )
  
### Misc
  
## To Do
       
  * Code Refactoring ( When I read the code of unreal engine4, I thought my engine's code is really messy. I should fix this! )
  * completly support D3D11, OpenGL                    
  * implement Hierarchical Shadow map       
  * Batch draw ( Fix up draw order )                    
   
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
 
## Development Blog

[Korean Blog](https://sungjjinkang.github.io/) 
