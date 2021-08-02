

# Modern Doom2 Project

## Why Do This Proeject
i had made some indie games with Unity game engine [Google PlayStore](https://play.google.com/store/apps/details?id=com.milli.findkiller2&hl=ko)  [Google PlayStore1](https://play.google.com/store/apps/details?id=com.NintyNineMillion.FindKiller&hl=ko).   
But Unity gives everything what I need. I didn't have to know How does Unity Engine work behind Editor UI.   
So Even if i had made many games for 3 years, i can't make just tiny game without Game Engine still.   

It's suck    

So I decided making game without game engine.     
And I choose Doom2 as My first game from sractch Project.     
Maybe i will make doom's voxel version and Add many things what i want ( like vehicle, guns...).    
I don't know How long it takes to complete this project.    
But I will complete this project!!    

And i never make game without game engine.     
So if you wanna good and clean code for learning something, Find other project.      

## Key features

  * C++17                   

## Implemented features

  * Profiler (reference : https://youtu.be/tD4xRNB0M_Q) 
  * Logger
  * Memory Pool(limited use)
  * Homemade Math Library (https://github.com/SungJJinKang/LightMath_Cpp)     
  * Homemade Asset Importer ( I tried to make everything from scratch. but Finally I decided just integrating many 3rd asset importers to one system)
  * Parallel ViewFrustum Culling (https://github.com/SungJJinKang/Frostbite_CullingSystem)
  * Distance Culling ( https://docs.unrealengine.com/en-US/RenderingAndGraphics/VisibilityCulling/CullDistanceVolume/index.html ) ( not used )
  * Support SIMD ( Currently AVX1 )
  * Occlusion Culling using HW Query( but not used )

## In Developing

  * Masked SW Occlusion Culling ( https://software.intel.com/content/dam/develop/external/us/en/documents/masked-software-occlusion-culling.pdf )      
  * ECS System ( Development Specification : https://docs.google.com/document/d/13eVWAFyuVbvDV7zYDqGF8kNTC8AtHP6lgMfDYTm1KXw/edit?usp=sharing )
## Dependency
I will try to make everything what i need.     
but i can't make some librarys like graphics api, audio api, some importers ....           

  * opengl 4.6       
  * glfw 3.3.2         
  * assimp       
  * DirectxTex        
  * concurrentqueue       
  * crossguid         
  * free type2       

## WARNING
On AMD on Board GPU, OpenGL sometimes makes driver error.      
Use NVIDEA GPU.     

## Coding Standard
[English](https://docs.google.com/document/d/1cT8EPgMXe0eopeHvwuFmbHG4TJr5kUmcovkr5irQZmo/edit)   
[Korean](https://docs.popekim.com/ko/coding-standards/cpp)

## Development Blog
[Korean Blog](https://sungjjinkang.github.io/) 

## Thanks
![WoCR0sCfffff](https://user-images.githubusercontent.com/33873804/103935734-5e92e300-516a-11eb-9afd-ab48b5f65791.png)
