#pragma once

#define GLOBAL_UNIFORM_BLOCK_BINDING_POINT 0
#define MAX_DIRECTIONAL_LIGHT_COUNT 5
#define MAX_POINT_LIGHT_COUNT 16

namespace dooms
{
	namespace graphics
	{
        enum eUniformBlock_Global
        {
			// trtansformations
			viewProjection = 0,
			prevViewProjection = 64,
			projection = 128,
			view = 192,
			invViewz = 256,
			// scene
			camPos = 320,
			// lighting
			dirLight0_Dir = 336,
			dirLight0_Col = 352,
			dirLight1_Dir = 368,
			dirLight1_Col = 384,
			dirLight2_Dir = 400,
			dirLight2_Col = 416,
			dirLight3_Dir = 432,
			dirLight3_Col = 448,
			dirLight4_Dir = 464,
			dirLight4_Col = 480,
			pointLight0_Pos = 496,
			pointLight0_Col = 512,
			pointLight1_Pos = 528,
			pointLight1_Col = 544,
			pointLight2_Pos = 560,
			pointLight2_Col = 576,
			pointLight3_Pos = 592,
			pointLight3_Col = 608,
			pointLight4_Pos = 624,
			pointLight4_Col = 640,
			pointLight5_Pos = 656,
			pointLight5_Col = 672,
			pointLight6_Pos = 688,
			pointLight6_Col = 704,
			pointLight7_Pos = 720,
			pointLight7_Col = 736,
			pointLight8_Pos = 752,
			pointLight8_Col = 768,
			pointLight9_Pos = 784,
			pointLight9_Col = 800,
			pointLight10_Pos = 816,
			pointLight10_Col = 832,
			pointLight11_Pos = 848,
			pointLight11_Col = 864,
			pointLight12_Pos = 880,
			pointLight12_Col = 896,
			pointLight13_Pos = 912,
			pointLight13_Col = 928,
			pointLight14_Pos = 944,
			pointLight14_Col = 960,
			pointLight15_Pos = 976,
			pointLight15_Col = 992,
			dirLightCount = 1008,
			pointLightCount = 1012,
			camNear = 1016,
			camFar = 1020,
			ambientLightIntensity = 1024,
        };
   

	}
}