#include "ReflectionTest.h"

#include "Macros/Path.h"
#include "Macros/Assert.h"
#include "Macros/MacrosHelper.h"

#include "UI/PrintText.h"

#include <cstring>

#include "../clReflectHelper.h"

#include <Transform.h>

#include "magic_enum.hpp"
#include "../ReflectionType/DEnum.h"
#include "Graphics/Color.h"

#include "ReflectionTest.reflection.h"

#include <Vector3.h>

namespace dooms
{
	enum DOOM_API D_ENUM TestEnum_ReflectionTest
	{
		test1 = 1,
		test2 = 3,
		test3 = 5,
		test4 = 444
	};

	struct DOOM_API D_STRUCT TestStruct_ReflectionTest : public DObject
	{
		GENERATE_BODY_FULLNAME_dooms__TestStruct_ReflectionTest()

		D_PROPERTY()
		int a = 2;

		D_PROPERTY()
		int b = 3;

		D_PROPERTY()
		int c = 6;

		D_PROPERTY()
		int* d = nullptr;

		//D_PROPERTY()
		//math::Vector3 vec3{ 0.0f, 1.0f, 2.0f };

		D_PROPERTY()
		TestEnum_ReflectionTest mTestEnum;
	};
}

void clReflectTest::test(clcpp::Database& db)
{


	{
		auto TestStruct_ReflectionTest_DClass = dooms::reflection::CreateDClass<dooms::TestStruct_ReflectionTest>();

		{
			dooms::reflection::DField property;
			const bool isPropertyReturned = TestStruct_ReflectionTest_DClass.GetField("a", property);
			D_ASSERT(isPropertyReturned == true);
			D_ASSERT(property.IsValid() == true);
			D_ASSERT(property.GetFieldTypeSize() == sizeof(int));
			D_ASSERT(std::strcmp(dPrimitiveHelper::GetShortNamePointer(property.GetFieldName()), "a") == 0);
		}
	
		{
			dooms::reflection::DField property;
			const bool isPropertyReturned = TestStruct_ReflectionTest_DClass.GetField("b", property);
			D_ASSERT(isPropertyReturned == true);
			D_ASSERT(property.IsValid() == true);
			D_ASSERT(property.GetFieldTypeSize() == sizeof(int));
			D_ASSERT(std::strcmp(dPrimitiveHelper::GetShortNamePointer(property.GetFieldName()), "b") == 0);

			dooms::TestStruct_ReflectionTest _TestStruct_ReflectionTest{};
			_TestStruct_ReflectionTest.b = 15;
			
			D_ASSERT(std::strcmp(property.ToString(&_TestStruct_ReflectionTest).data(), "15") == 0);

			bool isSuccessSettingFieldValue = property.SetRawValueToField(&_TestStruct_ReflectionTest, 10);
			D_ASSERT(isSuccessSettingFieldValue == true);
			D_ASSERT(std::strcmp(property.ToString(&_TestStruct_ReflectionTest).data(), "10") == 0);

			isSuccessSettingFieldValue = property.SetRawValueToField(&_TestStruct_ReflectionTest, 1);
			D_ASSERT(isSuccessSettingFieldValue == true);
			D_ASSERT(std::strcmp(property.ToString(&_TestStruct_ReflectionTest).data(), "1") == 0);
		}

		{
			dooms::reflection::DField property;
			const bool isPropertyReturned = TestStruct_ReflectionTest_DClass.GetField("mTestEnum", property);
			D_ASSERT(isPropertyReturned == true);
			D_ASSERT(property.IsValid() == true);
			D_ASSERT(property.GetFieldTypeSize() == sizeof(dooms::TestEnum_ReflectionTest));
			D_ASSERT(std::strcmp(dPrimitiveHelper::GetShortNamePointer(property.GetFieldName()), "mTestEnum") == 0);

			

			dooms::TestStruct_ReflectionTest _TestStruct_ReflectionTest{};
			_TestStruct_ReflectionTest.mTestEnum = dooms::TestEnum_ReflectionTest::test2;
			
			dooms::TestEnum_ReflectionTest* currentValue = property.GetFieldValue<dooms::TestEnum_ReflectionTest>(&_TestStruct_ReflectionTest);
			D_ASSERT(*currentValue == dooms::TestEnum_ReflectionTest::test2);
			
		}

		/*{
			for(const dooms::reflection::DField& dfield : TestStruct_ReflectionTest_DClass.GetFieldList())
			{
				dooms::ui::PrintText("VariableName : %s", dfield.GetFieldName());
				dooms::ui::PrintText("Type Size : %d", dfield.GetFieldTypeSize());
				dooms::ui::PrintText("Field Offset : %d", dfield.GetFieldOffset());
				dooms::ui::PrintText("Is pointer : %s", (dfield.GetFieldQualifier() == dooms::reflection::DField::eProperyQualifier::POINTER) ? "yes" : "no");
				dooms::ui::PrintText("-------------------------------------");
			}
		}*/
	}



	{
		const dooms::reflection::DEnum eTestEnum_ReflectionTestDEnum = dooms::reflection::CreateDEnum<dooms::TestEnum_ReflectionTest>();

		D_ASSERT(std::strcmp(eTestEnum_ReflectionTestDEnum.GetNameOfEnumConstantsValue(1), "test1") == 0);
		D_ASSERT(std::strcmp(eTestEnum_ReflectionTestDEnum.GetNameOfEnumConstantsValue(3), "test2") == 0);
		D_ASSERT(std::strcmp(eTestEnum_ReflectionTestDEnum.GetNameOfEnumConstantsValue(5), "test3") == 0);
		D_ASSERT(std::strcmp(eTestEnum_ReflectionTestDEnum.GetNameOfEnumConstantsValue(444), "test4") == 0);

		{
			INT32 value;
			const bool result = eTestEnum_ReflectionTestDEnum.GetValue("test1", value);
			D_ASSERT(result == true);
			D_ASSERT(value == 1);
		}

		{
			INT32 value;
			const bool result = eTestEnum_ReflectionTestDEnum.GetValue("test4", value);
			D_ASSERT(result == true);
			D_ASSERT(value == 444);
		}
	}




















	{
		auto DObjectName = db.GetName("dooms::DObject");
		auto DObjectType = db.GetType(DObjectName.hash);
		auto DObjectClass = DObjectType->AsClass();
		
	}

	{
		auto mat4x4Name = db.GetName("math::Matrix4x4");
		auto mat4x4Type = db.GetType(mat4x4Name.hash);
		auto mat4x4tClass = mat4x4Type->AsClass();

	}

	{
		auto transformName = db.GetName("dooms::Transform");
		auto transformType = db.GetType(transformName.hash);
		auto transformClass = transformType->AsClass();
		
	}

	{
		auto transform = dooms::reflection::CreateDClass<dooms::Transform>();

		dooms::reflection::DField property;
		const bool isPropertyReturned = transform.GetField("mTransformCoreData", property);
		D_ASSERT(isPropertyReturned == true);
		D_ASSERT(property.IsValid() == true);

		//property.GetPropertyValue<>()
	}



	{
		const dooms::reflection::DEnum eColorDEnum = dooms::reflection::CreateDEnum<dooms::graphics::eColor>();
		
		D_ASSERT(std::strcmp(eColorDEnum.GetNameOfEnumConstantsValue(0), "White") == 0);
		D_ASSERT(std::strcmp(eColorDEnum.GetNameOfEnumConstantsValue(1), "Black") == 0);
		D_ASSERT(std::strcmp(eColorDEnum.GetNameOfEnumConstantsValue(2), "Red") == 0);

		{
			INT32 value;
			const bool result = eColorDEnum.GetValue("Red", value);
			D_ASSERT(result == true);
			D_ASSERT(value == 2);
		}

		{
			INT32 value;
			const bool result = eColorDEnum.GetValue("White", value);
			D_ASSERT(result == true);
			D_ASSERT(value == 0);
		}

		{
			INT32 value;
			const bool result = eColorDEnum.GetValue("Test", value);
			D_ASSERT(result == false);
		}
	}

	unsigned num;
	const clcpp::Type** type = db.GetTypes(num);

	for (size_t i = 0; i < num; i++)
	{
		dooms::ui::PrintText(type[i]->name.text);
	}
}
