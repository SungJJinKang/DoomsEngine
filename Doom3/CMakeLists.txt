cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(Doom3 CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################
add_subdirectory(../MapEditor ${CMAKE_BINARY_DIR}/MapEditor)



























set(PROJECT_NAME Doom3)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../CodingRule.md"
    "../README.md"
    "Assets/Shader/common/brdf.txt"
    "Assets/Shader/common/constants.txt"
    "Assets/Shader/common/random.txt"
    "Assets/Shader/common/reflections.txt"
    "Assets/Shader/common/sampling.txt"
    "Assets/Shader/common/shadows.txt"
    "Assets/Shader/common/uniforms.txt"
    "Assets/Shader/Default/Billboard.glsl"
    "Assets/Shader/Default/Debug2DShader.glsl"
    "Assets/Shader/Default/Debug3DShader.glsl"
    "Assets/Shader/Default/Default2DColorShader.glsl"
    "Assets/Shader/Default/Default2DTextureShader.glsl"
    "Assets/Shader/Default/DefaultShader.glsl"
    "Assets/Shader/Default/DepthBufferTextureShader.glsl"
    "Assets/Shader/Default/equirect2cube_cs.glsl"
    "Assets/Shader/Default/GbufferDrawer.glsl"
    "Assets/Shader/Default/GbufferWriter_PBR.glsl"
    "Assets/Shader/Default/irmap_cs.glsl"
    "Assets/Shader/Default/OcclusionCullingBoundingBox.glsl"
    "Assets/Shader/Default/OverDrawVisualizationShader.glsl"
    "Assets/Shader/Default/skybox_fs.glsl"
    "Assets/Shader/Default/skybox_vs.glsl"
    "Assets/Shader/Default/spbrdf_cs.glsl"
    "Assets/Shader/Default/spmap_cs.glsl"
    "Assets/Shader/Default/tonemap_fs.glsl"
    "Assets/Shader/Default/tonemap_vs.glsl"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/bug.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/build_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/build_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/compat_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/compat_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/compile_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/compile_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/context_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/context_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/deprecated.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/dir_15a5176d7c9cc5c407ed4f611edf0684.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/dir_a58ef735c5cc5a9a31d321e1abe7c42e.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/dir_abae1f34c5d965773b98e3c915cdaeb5.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/dir_bc6505cac00d7a6291dbfd9af70666b7.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/files.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/glfw3_8h.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/glfw3_8h_source.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/glfw3native_8h.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/glfw3native_8h_source.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__buttons.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__context.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__errors.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__gamepad__axes.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__gamepad__buttons.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__hat__state.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__init.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__input.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__joysticks.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__keys.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__mods.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__monitor.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__native.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__shapes.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__vulkan.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/group__window.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/index.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/input_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/input_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/internal_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/internals_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/intro_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/intro_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/main_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/modules.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/monitor_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/monitor_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/moving_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/moving_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/news.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/news_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/pages.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/quick_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/quick_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_0.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_1.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_10.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_11.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_2.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_3.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_4.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_5.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_6.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_7.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_8.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_9.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_a.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_b.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_c.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_d.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_e.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/all_f.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/classes_0.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/defines_0.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/files_0.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/files_1.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/files_2.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/files_3.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/files_4.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/files_5.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/files_6.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/files_7.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/files_8.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/functions_0.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_0.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_1.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_2.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_3.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_4.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_5.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_6.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_7.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_8.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_9.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/groups_a.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/nomatches.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_0.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_1.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_2.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_3.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_4.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_5.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_6.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_7.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_8.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_9.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/pages_a.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/typedefs_0.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/variables_0.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/variables_1.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/variables_2.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/variables_3.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/variables_4.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/variables_5.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/variables_6.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/search/variables_7.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/structGLFWgamepadstate.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/structGLFWgammaramp.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/structGLFWimage.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/structGLFWvidmode.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/vulkan_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/vulkan_guide.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/window_8dox.html"
    "dependency/glfw-3.3.2.bin.WIN64/docs/html/window_guide.html"
    "Source/Core/Graphics/Acceleration/Culling.md"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/MaskedSWOcclusionCulling_HowWorks.md"
    "Source/Core/Graphics/ReadThis!!!!.txt"
    "Source/Core/Math/LightMath_Cpp/LICENSE"
    "Source/Core/Math/LightMath_Cpp/README.md"
    "Source/Core/ResourceManagement/JobSystem_cpp/MultithreadingJobSystemStrategy.md"
    "Source/Core/ResourceManagement/JobSystem_cpp/README.md"
    "Source/GameLogic/DeferredRenderingDebug.inl"
    "Source/Helper/DeferredConstant/.git"
    "Source/Helper/DeferredConstant/README.md"
    "Source/Helper/EasyDirtyChecker/README.md"
    "Source/Helper/ForLoop_Compile_Time/.git"
    "Source/Helper/ForLoop_Compile_Time/README.md"
    "Source/Helper/std_future_wrapper/.git"
    "Source/Helper/std_future_wrapper/README.md"
    "Source/Helper/vector_erase_move_lastelement/README.md"
    "TODO.txt"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "dependency/glad/include/glad/glad.h"
    "dependency/glad/include/KHR/khrplatform.h"
    "dependency/glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"
    "dependency/glfw-3.3.2.bin.WIN64/include/GLFW/glfw3native.h"
    "dependency/glfw/include/GLFW/glfw3.h"
    "dependency/imgui/imconfig.h"
    "dependency/imgui/imgui.h"
    "dependency/imgui/imgui_internal.h"
    "dependency/imgui/imstb_rectpack.h"
    "dependency/imgui/imstb_textedit.h"
    "dependency/imgui/imstb_truetype.h"
    "Source/Component/Core/Component.h"
    "Source/Component/Core/ComponentGlobals.h"
    "Source/Component/Core/PlainComponent.h"
    "Source/Component/Core/ServerComponent.h"
    "Source/Component/EventSystem.h"
    "Source/Component/PhysicsComponent/BoxCollider2D.h"
    "Source/Component/PhysicsComponent/BoxCollider3D.h"
    "Source/Component/PhysicsComponent/CapsuleCollider3D.h"
    "Source/Component/PhysicsComponent/CircleCollider2D.h"
    "Source/Component/PhysicsComponent/Collider2DComponent.h"
    "Source/Component/PhysicsComponent/Collider3DComponent.h"
    "Source/Component/PhysicsComponent/ColliderComponent.h"
    "Source/Component/PhysicsComponent/MeshCollider.h"
    "Source/Component/PhysicsComponent/Rigidbody/Rigidbody.h"
    "Source/Component/PhysicsComponent/SphereCollider3D.h"
    "Source/Component/Rendering/Animation/Animation.h"
    "Source/Component/Rendering/Animation/Animator.h"
    "Source/Component/Rendering/Camera.h"
    "Source/Component/Rendering/Light/DirectionalLight.h"
    "Source/Component/Rendering/Light/Light.h"
    "Source/Component/Rendering/Light/PointLight.h"
    "Source/Component/Rendering/Renderer/MeshRenderer.h"
    "Source/Component/Rendering/Renderer/Renderer.h"
    "Source/Component/Rendering/Renderer/RendererStaticIterator.h"
    "Source/Component/Transform.h"
    "Source/Core/API/ASSIMP.h"
    "Source/Core/API/Font.h"
    "Source/Core/API/OpenglAPI.h"
    "Source/Core/API/UUID.h"
    "Source/Core/Asset/Asset.h"
    "Source/Core/Asset/AssetHeaders.h"
    "Source/Core/Asset/AssetMetaData.h"
    "Source/Core/Asset/AssetsForwardDeclaration.h"
    "Source/Core/Asset/AudioAsset.h"
    "Source/Core/Asset/eAssetType.h"
    "Source/Core/Asset/FontAsset.h"
    "Source/Core/Asset/Helper/AssetFactory.h"
    "Source/Core/Asset/ShaderAsset.h"
    "Source/Core/Asset/TextAsset.h"
    "Source/Core/Asset/TextureAsset.h"
    "Source/Core/Asset/ThreeDModelAsset.h"
    "Source/Core/CompilerMacros.h"
    "Source/Core/ComponentPool/ComponentPool.h"
    "Source/Core/Core.h"
    "Source/Core/DObject/DObject.h"
    "Source/Core/DObject/DObjectGlobals.h"
    "Source/Core/DObject/DObjectMacros.h"
    "Source/Core/DObject/DObjectManager.h"
    "Source/Core/ECSSystem/easy_ecs/easy_ecs.h"
    "Source/Core/ECSSystem/easy_ecs/SparseSet.h"
    "Source/Core/Game/AssetManager/AssetContainer.h"
    "Source/Core/Game/AssetManager/AssetFuture.h"
    "Source/Core/Game/AssetManager/AssetManager.h"
    "Source/Core/Game/ConfigData.h"
    "Source/Core/Game/FrameDirtyChecker.h"
    "Source/Core/Game/GameCore.h"
    "Source/Core/Game/IGameFlow.h"
    "Source/Core/Graphics/Acceleration/CullDistance/CullDistance.h"
    "Source/Core/Graphics/Acceleration/CullDistance/CullDistanceRenderer.h"
    "Source/Core/Graphics/Acceleration/Culling.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/CullingModule.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/DistanceCulling/DistanceCulling.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/CoverageMask.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/MaskedSWOcclusionCulling.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Rasterizer/CoverageRasterizer.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Stage/BinTrianglesStage.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Stage/DepthTestOccludeeStage.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Stage/MaskedSWOcclusionCullingStage.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Stage/RasterizeTrianglesStage.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/SWDepthBuffer.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/OcclusionCullingWithComputeShader/OcclusionCullingWithComputeShader.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/QueryOcclusionCulling/QueryOcclusionCulling.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/ScreenSpaceBoundingSphereCulling/ScreenSpaceBoundingSphereCulling.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/ViewFrustumCulling/ViewFrustumCulling.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/EntityBlock.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/EntityBlockViewer.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/EntityGridCell.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/Math/AABB.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/Math/Common.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/Math/Matrix.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/Math/Triangle.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/Math/Vector.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/Position_BoundingSphereRadius.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/QueryObject.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/TransformData.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/VertexData.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/EveryCulling.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/EveryCullingCore.h"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/SIMD_Core.h"
    "Source/Core/Graphics/Acceleration/LinearViewFrustumCulling/DataStructure/EntityBlock.h"
    "Source/Core/Graphics/Acceleration/LinearViewFrustumCulling/DataStructure/EntityGridCell.h"
    "Source/Core/Graphics/Acceleration/LinearViewFrustumCulling/DataStructure/TransformData.h"
    "Source/Core/Graphics/Acceleration/LinearViewFrustumCulling/DataStructure/TrnasformHandle.h"
    "Source/Core/Graphics/Acceleration/LinearViewFrustumCulling/LinearViewFrustumCulling.h"
    "Source/Core/Graphics/Acceleration/LinearViewFrustumCulling/LinearViewFrustumCulling_Core.h"
    "Source/Core/Graphics/Acceleration/SortFrontToBackSolver.h"
    "Source/Core/Graphics/Batch/MeshBatchCreater.h"
    "Source/Core/Graphics/Buffer/Buffer.h"
    "Source/Core/Graphics/Buffer/BufferID.h"
    "Source/Core/Graphics/Buffer/Mesh.h"
    "Source/Core/Graphics/Buffer/MeshNode.h"
    "Source/Core/Graphics/Buffer/UniformBlockOffsetInfo.h"
    "Source/Core/Graphics/Buffer/UniformBufferObject.h"
    "Source/Core/Graphics/Buffer/UniformBufferObjectManager.h"
    "Source/Core/Graphics/Buffer/UniformBufferObjectUpdater.h"
    "Source/Core/Graphics/Color.h"
    "Source/Core/Graphics/DebugGraphics/DebugDrawer.h"
    "Source/Core/Graphics/DebugGraphics/OverDrawVisualization.h"
    "Source/Core/Graphics/DebugGraphics/RenderingDebugger.h"
    "Source/Core/Graphics/DeferredRenderingDrawer.h"
    "Source/Core/Graphics/ePrimitiveType.h"
    "Source/Core/Graphics/FrameBuffer/DefferedRenderingFrameBuffer.h"
    "Source/Core/Graphics/FrameBuffer/FrameBuffer.h"
    "Source/Core/Graphics/FrameBuffer/FrameBufferExporterHelper.h"
    "Source/Core/Graphics/FrameBuffer/RenderBuffer.h"
    "Source/Core/Graphics/Graphics_Core.h"
    "Source/Core/Graphics/Graphics_Server.h"
    "Source/Core/Graphics/Graphics_Setting.h"
    "Source/Core/Graphics/GraphicsAPI.h"
    "Source/Core/Graphics/GraphicsAPIManager.h"
    "Source/Core/Graphics/LightManager.h"
    "Source/Core/Graphics/Material/FixedMaterial.h"
    "Source/Core/Graphics/Material/Material.h"
    "Source/Core/Graphics/OverlapBindChecker.h"
    "Source/Core/Graphics/PictureInPicture/PicktureInPickture.h"
    "Source/Core/Graphics/PictureInPicture/PIPManager.h"
    "Source/Core/Graphics/PrimitiveType/PrimitiveLine.h"
    "Source/Core/Graphics/PrimitiveType/PrimitiveTriangle.h"
    "Source/Core/Graphics/RenderingBitFlag.h"
    "Source/Core/Graphics/Texture/CubemapTexture.h"
    "Source/Core/Graphics/Texture/SingleTexture.h"
    "Source/Core/Graphics/Texture/Texture.h"
    "Source/Core/Graphics/TextureFormat.h"
    "Source/Core/IO/AssetExporter/AssetExporter_Texture.h"
    "Source/Core/IO/AssetImporter/AssetImporter.h"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker.h"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Audio.h"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Font.h"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Shader.h"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Text.h"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Texture.h"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Three_D_Model.h"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorkerForwardDeclaration.h"
    "Source/Core/IO/AssetImporter/Manager/AssetImporterWorkerManager.h"
    "Source/Core/IO/KEY_CODE.h"
    "Source/Core/IO/UserInput_Server.h"
    "Source/Core/IO/UserInputHelper.h"
    "Source/Core/Logger/Logger.h"
    "Source/Core/Macros/Assert.h"
    "Source/Core/Macros/DllMarcos.h"
    "Source/Core/Macros/Log.h"
    "Source/Core/Macros/Macros.h"
    "Source/Core/Macros/MacrosHelper.h"
    "Source/Core/Macros/Path.h"
    "Source/Core/Macros/Profiling.h"
    "Source/Core/Macros/TypeDef.h"
    "Source/Core/Math/LightMath_Cpp/Collision.h"
    "Source/Core/Math/LightMath_Cpp/Euler.h"
    "Source/Core/Math/LightMath_Cpp/LMath.h"
    "Source/Core/Math/LightMath_Cpp/LMath_Core.h"
    "Source/Core/Math/LightMath_Cpp/Matrix.h"
    "Source/Core/Math/LightMath_Cpp/Matrix1x1.h"
    "Source/Core/Math/LightMath_Cpp/Matrix2x2.h"
    "Source/Core/Math/LightMath_Cpp/Matrix3x3.h"
    "Source/Core/Math/LightMath_Cpp/Matrix4x4.h"
    "Source/Core/Math/LightMath_Cpp/Matrix4x4Float_SIMD.inl"
    "Source/Core/Math/LightMath_Cpp/Matrix_utility.h"
    "Source/Core/Math/LightMath_Cpp/Quaternion.h"
    "Source/Core/Math/LightMath_Cpp/Quaternion_Scalar.h"
    "Source/Core/Math/LightMath_Cpp/Quaternion_SIMD.h"
    "Source/Core/Math/LightMath_Cpp/SIMD.h"
    "Source/Core/Math/LightMath_Cpp/SIMD_Core.h"
    "Source/Core/Math/LightMath_Cpp/Trigonometric.h"
    "Source/Core/Math/LightMath_Cpp/Utility.h"
    "Source/Core/Math/LightMath_Cpp/Vector.h"
    "Source/Core/Math/LightMath_Cpp/Vector1.h"
    "Source/Core/Math/LightMath_Cpp/Vector2.h"
    "Source/Core/Math/LightMath_Cpp/Vector3.h"
    "Source/Core/Math/LightMath_Cpp/Vector4.h"
    "Source/Core/Math/LightMath_Cpp/Vector4Float_SIMD.inl"
    "Source/Core/Math/Math.h"
    "Source/Core/Math/Matrix.h"
    "Source/Core/Math/Matrix1x1.h"
    "Source/Core/Math/Matrix2x2.h"
    "Source/Core/Math/Matrix3x3.h"
    "Source/Core/Math/Matrix4x4.h"
    "Source/Core/Math/Quaternion.h"
    "Source/Core/Math/Utility.h"
    "Source/Core/Math/Vector.h"
    "Source/Core/Math/Vector1.h"
    "Source/Core/Math/Vector2.h"
    "Source/Core/Math/Vector3.h"
    "Source/Core/Math/Vector4.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Math.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Matrix.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Matrix1x1.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Matrix2x2.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Matrix3x3.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Matrix4x4.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Quaternion.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Utility.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Vector.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Vector1.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Vector2.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Vector3.h"
    "Source/Core/Math/VeryLight_Math_For_Game/Vector4.h"
    "Source/Core/OS/OS.h"
    "Source/Core/Physics/Collider/AABB.h"
    "Source/Core/Physics/Collider/CapsuleCollider.h"
    "Source/Core/Physics/Collider/Circle2D.h"
    "Source/Core/Physics/Collider/Collider.h"
    "Source/Core/Physics/Collider/ColliderSolution.h"
    "Source/Core/Physics/Collider/ColliderType.h"
    "Source/Core/Physics/Collider/Line.h"
    "Source/Core/Physics/Collider/OBB.h"
    "Source/Core/Physics/Collider/PhysicsGeneric.h"
    "Source/Core/Physics/Collider/Plane.h"
    "Source/Core/Physics/Collider/Ray.h"
    "Source/Core/Physics/Collider/RenderCollider.h"
    "Source/Core/Physics/Collider/Sphere.h"
    "Source/Core/Physics/ColliderPickingTestRoom.h"
    "Source/Core/Physics/Phycis_Core.h"
    "Source/Core/Physics/Physics_Server.h"
    "Source/Core/Physics/Physics_Setting.h"
    "Source/Core/Physics/PhysicsDebugger.h"
    "Source/Core/Physics/PhysicsSolver.h"
    "Source/Core/Physics/Picking.h"
    "Source/Core/Profiler/CPUVendorProfiler.h"
    "Source/Core/Profiler/ProfilerABTest.h"
    "Source/Core/Profiler/ProfilerUI.h"
    "Source/Core/Random.h"
    "Source/Core/ResourceManagement/JobSystem_cpp/JobSystem.h"
    "Source/Core/ResourceManagement/JobSystem_cpp/Thread.h"
    "Source/Core/ResourceManagement/JobSystem_cpp/Thread_Core.h"
    "Source/Core/ResourceManagement/JobSystem_cpp/ThreadProfiler.h"
    "Source/Core/ResourceManagement/Pool/MemoryPool.h"
    "Source/Core/ResourceManagement/Pool/ObjectPool.h"
    "Source/Core/Scene/Entity.h"
    "Source/Core/Scene/IWorldIndependent.h"
    "Source/Core/Scene/Layer.h"
    "Source/Core/Scene/Scene.h"
    "Source/Core/Scene/SharedScene.h"
    "Source/Core/Scene/SharedSceneSetting.h"
    "Source/Core/Time/MainTimer.h"
    "Source/Core/Time/Time_Server.h"
    "Source/Core/UI/PrintText.h"
    "Source/Core/utility/BVH/BVH.h"
    "Source/Core/utility/BVH/BVH_Core.h"
    "Source/Core/utility/BVH/BVH_Node.h"
    "Source/Core/utility/BVH/BVH_Node_Container.h"
    "Source/Core/utility/BVH/BVH_Node_Object.h"
    "Source/Core/utility/BVH/BVH_Node_View.h"
    "Source/Core/utility/BVH/extension/BVH_AxisSweep3.h"
    "Source/Core/utility/BVH/test/BVH_TestRoom.h"
    "Source/Core/utility/ColliderUpdater.h"
    "Source/Core/utility/ITester.h"
    "Source/Core/utility/KDTree/KDTree.h"
    "Source/Core/utility/KDTree/KDTreeCore.h"
    "Source/Core/utility/KDTree/KDTreeNode.h"
    "Source/Core/utility/KDTree/KDTreeNodeView.h"
    "Source/Core/utility/KDTree/test/KDTree_TestRoom.h"
    "Source/Core/utility/SimpleIniParser.h"
    "Source/Core/utility/TextImporter.h"
    "Source/Core/utility/Tree.h"
    "Source/Core/utility/TreeNode.h"
    "Source/Core/utility/trim.h"
    "Source/Core/WorldEditor/MapLoader.h"
    "Source/GameLogic/CustomComponent/AutoRotate.h"
    "Source/GameLogic/CustomComponent/AutoRotateAround.h"
    "Source/GameLogic/CustomComponent/AxisDebugger.h"
    "Source/GameLogic/CustomComponent/BoxAdder.h"
    "Source/GameLogic/CustomComponent/BulletComponent.h"
    "Source/GameLogic/CustomComponent/ButtonRotate.h"
    "Source/GameLogic/CustomComponent/CharacterSpawner.h"
    "Source/GameLogic/CustomComponent/ExportTextureTester.h"
    "Source/GameLogic/CustomComponent/FireBulletComponent.h"
    "Source/GameLogic/CustomComponent/Move_WASD.h"
    "Source/GameLogic/CustomComponent/PerformanceTestController.h"
    "Source/GameLogic/CustomComponent/Portfolio/DeferredRenderingDebuggerController.h"
    "Source/GameLogic/CustomComponent/Portfolio/OverDrawVisualizationDebugger.h"
    "Source/GameLogic/CustomComponent/Portfolio/PhysicsDebuggerController.h"
    "Source/GameLogic/CustomComponent/Portfolio/PortfolioComponent.h"
    "Source/GameLogic/CustomComponent/Portfolio/RenderingAABBController.h"
    "Source/GameLogic/CustomComponent/Portfolio/ViewFrustumCullingDebug.h"
    "Source/GameLogic/CustomComponent/TestComponent.h"
    "Source/GameLogic/Doom_Core.h"
    "Source/GameLogic/GameLogicStartPoint.h"
    "Source/GameLogic/OverDrawVisualizationTest.inl"
    "Source/GameLogic/Portfolio.inl"
    "Source/GameLogic/RayCastTest.inl"
    "Source/GameLogic/ViewFrustumCullingDebug.inl"
    "Source/Helper/concurrentqueue/blockingconcurrentqueue.h"
    "Source/Helper/crossguid/Guid.hpp"
    "Source/Helper/DeferredConstant/DeferredConstant.h"
    "Source/Helper/EasyDirtyChecker/DirtyReceiver.h"
    "Source/Helper/EasyDirtyChecker/DirtySender.h"
    "Source/Helper/ForLoop_Compile_Time/ForLoop_Compile.h"
    "Source/Helper/magic_enum.hpp"
    "Source/Helper/Simple_SingleTon/Singleton.h"
    "Source/Helper/StaticContainer/StaticContainer.h"
    "Source/Helper/std_future_wrapper/CustomFutureWrapper.h"
    "Source/Helper/std_future_wrapper/DummyFuture.h"
    "Source/Helper/std_future_wrapper/FutureWrapper.h"
    "Source/Helper/std_future_wrapper/shared_future/CustomSharedFuture.h"
    "Source/Helper/std_future_wrapper/shared_future/DummySharedFuture.h"
    "Source/Helper/std_future_wrapper/shared_future/StdSharedFuture.h"
    "Source/Helper/std_future_wrapper/StdFuture.h"
    "Source/Helper/vector_erase_move_lastelement/vector_swap_erase.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "main.cpp"
    "Source/Component/Core/Component.cpp"
    "Source/Component/Core/PlainComponent.cpp"
    "Source/Component/Core/ServerComponent.cpp"
    "Source/Component/EventSystem.cpp"
    "Source/Component/PhysicsComponent/BoxCollider2D.cpp"
    "Source/Component/PhysicsComponent/BoxCollider3D.cpp"
    "Source/Component/PhysicsComponent/CapsuleCollider3D.cpp"
    "Source/Component/PhysicsComponent/CircleCollider2D.cpp"
    "Source/Component/PhysicsComponent/Collider2DComponent.cpp"
    "Source/Component/PhysicsComponent/Collider3DComponent.cpp"
    "Source/Component/PhysicsComponent/ColliderComponent.cpp"
    "Source/Component/PhysicsComponent/MeshCollider.cpp"
    "Source/Component/PhysicsComponent/Rigidbody/Rigidbody.cpp"
    "Source/Component/PhysicsComponent/SphereCollider3D.cpp"
    "Source/Component/Rendering/Animation/Animation.cpp"
    "Source/Component/Rendering/Animation/Animator.cpp"
    "Source/Component/Rendering/Camera.cpp"
    "Source/Component/Rendering/Light/DirectionalLight.cpp"
    "Source/Component/Rendering/Light/Light.cpp"
    "Source/Component/Rendering/Light/PointLight.cpp"
    "Source/Component/Rendering/Renderer/MeshRenderer.cpp"
    "Source/Component/Rendering/Renderer/Renderer.cpp"
    "Source/Component/Rendering/Renderer/RendererStaticIterator.cpp"
    "Source/Component/Transform.cpp"
    "Source/Core/Asset/Asset.cpp"
    "Source/Core/Asset/AudioAsset.cpp"
    "Source/Core/Asset/FontAsset.cpp"
    "Source/Core/Asset/Helper/AssetFactory.cpp"
    "Source/Core/Asset/ShaderAsset.cpp"
    "Source/Core/Asset/TextAsset.cpp"
    "Source/Core/Asset/TextureAsset.cpp"
    "Source/Core/Asset/ThreeDModelAsset.cpp"
    "Source/Core/DObject/DObject.cpp"
    "Source/Core/DObject/DObjectManager.cpp"
    "Source/Core/ECSSystem/easy_ecs/easy_ecs.cpp"
    "Source/Core/Game/AssetManager/AssetContainer.cpp"
    "Source/Core/Game/AssetManager/AssetFuture.cpp"
    "Source/Core/Game/AssetManager/AssetManager.cpp"
    "Source/Core/Game/FrameDirtyChecker.cpp"
    "Source/Core/Game/GameCore.cpp"
    "Source/Core/Game/IGameFlow.cpp"
    "Source/Core/Graphics/Acceleration/CullDistance/CullDistance.cpp"
    "Source/Core/Graphics/Acceleration/CullDistance/CullDistanceRenderer.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/CullingModule.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/DistanceCulling/DistanceCulling.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/MaskedSWOcclusionCulling.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Rasterizer/CoverageRasterizer.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Stage/BinTrianglesStage.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Stage/DepthTestOccludeeStage.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Stage/MaskedSWOcclusionCullingStage.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Stage/RasterizeTrianglesStage.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/SWDepthBuffer.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/OcclusionCullingWithComputeShader/OcclusionCullingWithComputeShader.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/QueryOcclusionCulling/QueryOcclusionCulling.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/ScreenSpaceBoundingSphereCulling/ScreenSpaceBoundingSphereCulling.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/ViewFrustumCulling/ViewFrustumCulling.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/EntityBlockViewer.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/Math/Common.cpp"
    "Source/Core/Graphics/Acceleration/LinearData_ViewFrustumCulling/EveryCulling.cpp"
    "Source/Core/Graphics/Acceleration/SortFrontToBackSolver.cpp"
    "Source/Core/Graphics/Batch/MeshBatchCreater.cpp"
    "Source/Core/Graphics/Buffer/Buffer.cpp"
    "Source/Core/Graphics/Buffer/Mesh.cpp"
    "Source/Core/Graphics/Buffer/UniformBufferObject.cpp"
    "Source/Core/Graphics/Buffer/UniformBufferObjectManager.cpp"
    "Source/Core/Graphics/Buffer/UniformBufferObjectUpdater.cpp"
    "Source/Core/Graphics/Color.cpp"
    "Source/Core/Graphics/DebugGraphics/DebugDrawer.cpp"
    "Source/Core/Graphics/DebugGraphics/OverDrawVisualization.cpp"
    "Source/Core/Graphics/DebugGraphics/RenderingDebugger.cpp"
    "Source/Core/Graphics/DeferredRenderingDrawer.cpp"
    "Source/Core/Graphics/FrameBuffer/DefferedRenderingFrameBuffer.cpp"
    "Source/Core/Graphics/FrameBuffer/FrameBuffer.cpp"
    "Source/Core/Graphics/FrameBuffer/FrameBufferExporterHelper.cpp"
    "Source/Core/Graphics/FrameBuffer/RenderBuffer.cpp"
    "Source/Core/Graphics/Graphics_Server.cpp"
    "Source/Core/Graphics/Graphics_Setting.cpp"
    "Source/Core/Graphics/GraphicsAPI.cpp"
    "Source/Core/Graphics/GraphicsAPIManager.cpp"
    "Source/Core/Graphics/LightManager.cpp"
    "Source/Core/Graphics/Material/FixedMaterial.cpp"
    "Source/Core/Graphics/Material/Material.cpp"
    "Source/Core/Graphics/OverlapBindChecker.cpp"
    "Source/Core/Graphics/PictureInPicture/PicktureInPickture.cpp"
    "Source/Core/Graphics/PictureInPicture/PIPManager.cpp"
    "Source/Core/Graphics/PrimitiveType/PrimitiveLine.cpp"
    "Source/Core/Graphics/PrimitiveType/PrimitiveTriangle.cpp"
    "Source/Core/Graphics/Texture/CubemapTexture.cpp"
    "Source/Core/Graphics/Texture/SingleTexture.cpp"
    "Source/Core/Graphics/Texture/Texture.cpp"
    "Source/Core/IO/AssetExporter/AssetExporter_Texture.cpp"
    "Source/Core/IO/AssetImporter/AssetImporter.cpp"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker.cpp"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Audio.cpp"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Font.cpp"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Shader.cpp"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Text.cpp"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Texture.cpp"
    "Source/Core/IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Three_D_Model.cpp"
    "Source/Core/IO/AssetImporter/Manager/AssetImporterWorkerManager.cpp"
    "Source/Core/IO/KEY_CODE.cpp"
    "Source/Core/IO/UserInput_Server.cpp"
    "Source/Core/IO/UserInputHelper.cpp"
    "Source/Core/Logger/Logger.cpp"
    "Source/Core/Macros/Path.cpp"
    "Source/Core/Math/LightMath_Cpp/Matrix.cpp"
    "Source/Core/Math/LightMath_Cpp/Vector1.cpp"
    "Source/Core/Math/LightMath_Cpp/Vector2.cpp"
    "Source/Core/Math/LightMath_Cpp/Vector3.cpp"
    "Source/Core/Math/LightMath_Cpp/Vector4.cpp"
    "Source/Core/OS/Window.cpp"
    "Source/Core/Physics/Collider/AABB.cpp"
    "Source/Core/Physics/Collider/CapsuleCollider.cpp"
    "Source/Core/Physics/Collider/Circle2D.cpp"
    "Source/Core/Physics/Collider/Collider.cpp"
    "Source/Core/Physics/Collider/ColliderSolution.cpp"
    "Source/Core/Physics/Collider/ColliderType.cpp"
    "Source/Core/Physics/Collider/Line.cpp"
    "Source/Core/Physics/Collider/OBB.cpp"
    "Source/Core/Physics/Collider/PhysicsGeneric.cpp"
    "Source/Core/Physics/Collider/Plane.cpp"
    "Source/Core/Physics/Collider/Ray.cpp"
    "Source/Core/Physics/Collider/RenderCollider.cpp"
    "Source/Core/Physics/Collider/Sphere.cpp"
    "Source/Core/Physics/ColliderPickingTestRoom.cpp"
    "Source/Core/Physics/Physics_Server.cpp"
    "Source/Core/Physics/Physics_Setting.cpp"
    "Source/Core/Physics/PhysicsDebugger.cpp"
    "Source/Core/Physics/PhysicsSolver.cpp"
    "Source/Core/Physics/Picking.cpp"
    "Source/Core/Profiler/ProfilerUI.cpp"
    "Source/Core/Random.cpp"
    "Source/Core/ResourceManagement/JobSystem_cpp/JobSystem.cpp"
    "Source/Core/ResourceManagement/JobSystem_cpp/test/test.cpp"
    "Source/Core/ResourceManagement/JobSystem_cpp/Thread.cpp"
    "Source/Core/ResourceManagement/JobSystem_cpp/ThreadProfiler.cpp"
    "Source/Core/ResourceManagement/Pool/MemoryPool.cpp"
    "Source/Core/Scene/Entity.cpp"
    "Source/Core/Scene/Scene.cpp"
    "Source/Core/Scene/SharedScene.cpp"
    "Source/Core/Scene/SharedSceneSetting.cpp"
    "Source/Core/Time/MainTimer.cpp"
    "Source/Core/Time/Time_Server.cpp"
    "Source/Core/UI/PrintText.cpp"
    "Source/Core/utility/BVH/BVH.cpp"
    "Source/Core/utility/BVH/BVH_Node.cpp"
    "Source/Core/utility/BVH/BVH_Node_Container.cpp"
    "Source/Core/utility/BVH/BVH_Node_Object.cpp"
    "Source/Core/utility/BVH/BVH_Node_View.cpp"
    "Source/Core/utility/BVH/extension/BVH_AxisSweep3.cpp"
    "Source/Core/utility/BVH/test/BVH_TestRoom.cpp"
    "Source/Core/utility/ColliderUpdater.cpp"
    "Source/Core/utility/KDTree/KDTree.cpp"
    "Source/Core/utility/KDTree/KDTreeAABB.cpp"
    "Source/Core/utility/KDTree/KDTreeNodeView.cpp"
    "Source/Core/utility/KDTree/KDTreeVector.cpp"
    "Source/Core/utility/KDTree/test/KDTree_TestRoom.cpp"
    "Source/Core/utility/SimpleIniParser.cpp"
    "Source/Core/utility/TextImporter.cpp"
    "Source/Core/WorldEditor/MapLoader.cpp"
    "Source/GameLogic/CustomComponent/AutoRotate.cpp"
    "Source/GameLogic/CustomComponent/AutoRotateAround.cpp"
    "Source/GameLogic/CustomComponent/AxisDebugger.cpp"
    "Source/GameLogic/CustomComponent/BoxAdder.cpp"
    "Source/GameLogic/CustomComponent/BulletComponent.cpp"
    "Source/GameLogic/CustomComponent/ButtonRotate.cpp"
    "Source/GameLogic/CustomComponent/CharacterSpawner.cpp"
    "Source/GameLogic/CustomComponent/ExportTextureTester.cpp"
    "Source/GameLogic/CustomComponent/FireBulletComponent.cpp"
    "Source/GameLogic/CustomComponent/Move_WASD.cpp"
    "Source/GameLogic/CustomComponent/PerformanceTestController.cpp"
    "Source/GameLogic/CustomComponent/Portfolio/DeferredRenderingDebuggerController.cpp"
    "Source/GameLogic/CustomComponent/Portfolio/OverDrawVisualizationDebugger.cpp"
    "Source/GameLogic/CustomComponent/Portfolio/PhysicsDebuggerController.cpp"
    "Source/GameLogic/CustomComponent/Portfolio/PortfolioComponent.cpp"
    "Source/GameLogic/CustomComponent/Portfolio/RenderingAABBController.cpp"
    "Source/GameLogic/CustomComponent/Portfolio/ViewFrustumCullingDebug.cpp"
    "Source/GameLogic/CustomComponent/TestComponent.cpp"
    "Source/GameLogic/GameLogicStartPoint.cpp"
    "Source/Helper/EasyDirtyChecker/DirtyReceiver.cpp"
    "Source/Helper/EasyDirtyChecker/DirtySender.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Doom3)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Release>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/Source/thirdparty/amdUprof/include"
        ">"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/OS;"
        "$ENV{VcpkgInstalledDir}x64-windows/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Helper;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Component;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Scene;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Component/Core;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Helper/crossguid;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/GameLogic/CustomComponent;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Math/LightMath_Cpp;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/IO;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Time;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/GameLogic;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Logger;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Physics;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/utility"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/OS;"
        "$ENV{VcpkgInstalledDir}x86-windows/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Helper;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Component;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Scene;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Component/Core;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Helper/crossguid;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/GameLogic/CustomComponent;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Math/LightMath_Cpp;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/IO;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Time;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/GameLogic;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Logger;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Physics;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/utility"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "DOOM_DLL_EXPORTS;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "DOOM_DLL_EXPORTS;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:Release>:
                /Oi;
                /Gy;
                /Zi
            >
            /permissive-;
            /MP;
            /std:c++17;
            /sdl;
            /arch:AVX;
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /MP;
            /std:c++17;
            /sdl;
            /arch:AVX;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Release>:"
            "AMDProfileController"
        ">"
        "xg;"
        "ntdll"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "xg"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "${CMAKE_SOURCE_DIR}/Source/Helper/crossguid/build/Debug"
        ">"
        "$<$<CONFIG:Release>:"
            "${CMAKE_SOURCE_DIR}/Source/thirdparty/amdUprof/lib/x64;"
            "${CMAKE_SOURCE_DIR}/Source/Helper/crossguid/build/Release"
        ">"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "${CMAKE_SOURCE_DIR}/Source/Helper/crossguid/build/Debug"
        ">"
        "$<$<CONFIG:Release>:"
            "${CMAKE_SOURCE_DIR}/dependency/Compressonator/lib/VS2017/x86;"
            "${CMAKE_SOURCE_DIR}/dependency/assimp;"
            "${CMAKE_SOURCE_DIR}/dependency/glfw/lib;"
            "${CMAKE_SOURCE_DIR}/dependency/crossguid/build/Release;"
            "${CMAKE_SOURCE_DIR}/Source/Helper/crossguid/build/Release"
        ">"
    )
endif()

