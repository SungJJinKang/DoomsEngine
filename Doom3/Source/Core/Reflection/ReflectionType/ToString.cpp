#include "ToString.h"

#include <Math/LightMath_Cpp/LMath.h>

namespace dooms
{
	namespace reflection
	{
		namespace toStringDetails
		{
			template <typename T>
			std::string ToStringTemplate(const void* const object)
			{
				return std::to_string(*reinterpret_cast<const T*>(object));
			}
			
			std::string ToStringBoolean(const void* const object)
			{
				return (*reinterpret_cast<const bool*>(object) == true) ? "True" : "False";
			}


			std::string ToStringStdString(const void* const object)
			{
				return *reinterpret_cast<const std::string*>(object);
			}

			std::string ToStringConstCharPointer(const void* const object)
			{
				return *reinterpret_cast<const char* const*>(object);
			}

			std::string ToStringMat2x2(const void* const object)
			{
				std::string str;

				const math::Matrix2x2* const mat2x2 = reinterpret_cast<const math::Matrix2x2*>(object);

				for (size_t i = 0; i < 2; i++)
				{
					for (size_t j = 0; j < 2; j++)
					{
						str += std::to_string(mat2x2->columns[j][i]);

						if (j != 1)
						{
							str += " ";
						}
					}

					if (i != 1)
					{
						str += "\n";
					}
				}

				return str;
			}

			std::string ToStringMat3x3(const void* const object)
			{
				std::string str;

				const math::Matrix3x3* const mat3x3 = reinterpret_cast<const math::Matrix3x3*>(object);

				for(size_t i = 0 ; i < 3 ; i++)
				{
					for (size_t j = 0; j < 3; j++)
					{
						str += std::to_string(mat3x3->columns[j][i]);

						if (j != 2)
						{
							str += " ";
						}
					}

					if(i != 2)
					{
						str += "\n";
					}
				}

				return str;
			}

			std::string ToStringMat4x4(const void* const object)
			{
				std::string str;

				const math::Matrix4x4* const mat4x4 = reinterpret_cast<const math::Matrix4x4*>(object);

				for (size_t i = 0; i < 4; i++)
				{
					for (size_t j = 0; j < 4; j++)
					{
						str += std::to_string(mat4x4->columns[j][i]);

						if (j != 3)
						{
							str += " ";
						}
					}

					if (i != 3)
					{
						str += "\n";
					}
				}

				return str;
			}


			std::string ToStringVec2(const void* const object)
			{
				std::string str;

				const math::Vector2* const vec2 = reinterpret_cast<const math::Vector2*>(object);

				for (size_t i = 0; i < 2; i++)
				{
					str += std::to_string(*(vec2->data() + i));

					if (i != 1)
					{
						str += " ";
					}
				}

				return str;
			}

			std::string ToStringVec3(const void* const object)
			{
				std::string str;

				const math::Vector3* const vec3 = reinterpret_cast<const math::Vector3*>(object);

				for (size_t i = 0; i < 3; i++)
				{
					str += std::to_string(*(vec3->data() + i));

					if (i != 2)
					{
						str += " ";
					}
				}

				return str;
			}

			std::string ToStringVec4(const void* const object)
			{
				std::string str;

				const math::Vector4* const vec4 = reinterpret_cast<const math::Vector4*>(object);

				for (size_t i = 0; i < 4; i++)
				{
					str += std::to_string(*(vec4->data() + i));

					if (i != 3)
					{
						str += " ";
					}
				}

				return str;
			}
		}

		/// <summary>
		/// key : reflection hash value
		///	value : To String Function Pointer
		/// </summary>
		static std::unordered_map<UINT32, dooms::reflection::TO_STRING_FUNC> ReflectionToStringFunc{};
		static bool isInitialized = false;

		static void AddReflectionToStringFunc(const UINT32 typeHashValue, TO_STRING_FUNC toStringFunc)
		{
			ReflectionToStringFunc[typeHashValue] = toStringFunc;
		}

		void InitReflectionToString()
		{
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<UINT8>(), toStringDetails::ToStringTemplate<UINT8>);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<UINT16>(), toStringDetails::ToStringTemplate<UINT16>);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<UINT32>(), toStringDetails::ToStringTemplate<UINT32>);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<UINT64>(), toStringDetails::ToStringTemplate<UINT64>);
			//AddReflectionToStringFunc(clcpp::GetTypeNameHash<INT8>(), toStringDetails::ToStringTemplate<INT8>);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<INT16>(), toStringDetails::ToStringTemplate<INT16>);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<INT32>(), toStringDetails::ToStringTemplate<INT32>);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<INT64>(), toStringDetails::ToStringTemplate<INT64>);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<FLOAT32>(), toStringDetails::ToStringTemplate<FLOAT32>);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<FLOAT64>(), toStringDetails::ToStringTemplate<FLOAT64>);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<bool>(), toStringDetails::ToStringBoolean);

			//AddReflectionToStringFunc(clcpp::GetTypeNameHash<std::string>(), toStringDetails::ToStringStdString);
			//AddReflectionToStringFunc(clcpp::GetTypeNameHash<const char*>(), toStringDetails::ToStringConstCharPointer);

			AddReflectionToStringFunc(clcpp::GetTypeNameHash<math::Matrix2x2>(), toStringDetails::ToStringMat2x2);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<math::Matrix3x3>(), toStringDetails::ToStringMat3x3);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<math::Matrix4x4>(), toStringDetails::ToStringMat4x4);

			AddReflectionToStringFunc(clcpp::GetTypeNameHash<math::Vector2>(), toStringDetails::ToStringVec2);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<math::Vector3>(), toStringDetails::ToStringVec3);
			AddReflectionToStringFunc(clcpp::GetTypeNameHash<math::Vector4>(), toStringDetails::ToStringVec4);


			isInitialized = true;
		}

		std::string GetStringFromReflectionData(const UINT32 reflectionHashValue, const void* const object)
		{
			D_ASSERT_LOG(isInitialized == true, "Please Call ToString::InitReflectionToString");
			D_ASSERT_LOG(ReflectionToStringFunc.find(reflectionHashValue) != ReflectionToStringFunc.end(), "Fail to Find ReflectionToStringFunc");

			return ReflectionToStringFunc[reflectionHashValue](object);
		}
	}
}