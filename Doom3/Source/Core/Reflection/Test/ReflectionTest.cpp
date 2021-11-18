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
		int a;

		D_PROPERTY()
		int b;

		D_PROPERTY()
		int c;

		D_PROPERTY()
		int* d;

		D_PROPERTY()
		TestEnum_ReflectionTest mTestEnum;
	};
}

void clReflectTest::test(clcpp::Database& db)
{


	{
		auto TestStruct_ReflectionTest_DClass = dooms::CreateDClass<dooms::TestStruct_ReflectionTest>();

		{
			dooms::DField property;
			const bool isPropertyReturned = TestStruct_ReflectionTest_DClass.GetField("a", property);
			D_ASSERT(isPropertyReturned == true);
			D_ASSERT(property.IsValid() == true);
			D_ASSERT(property.GetFieldTypeSize() == sizeof(int));
			D_ASSERT(std::strcmp(dPrimitiveHelper::GetShortNamePointer(property.GetFieldVariableFullName()), "a") == 0);
		}
	
		{
			dooms::DField property;
			const bool isPropertyReturned = TestStruct_ReflectionTest_DClass.GetField("b", property);
			D_ASSERT(isPropertyReturned == true);
			D_ASSERT(property.IsValid() == true);
			D_ASSERT(property.GetFieldTypeSize() == sizeof(int));
			D_ASSERT(std::strcmp(dPrimitiveHelper::GetShortNamePointer(property.GetFieldVariableFullName()), "b") == 0);
		}

		{
			dooms::DField property;
			const bool isPropertyReturned = TestStruct_ReflectionTest_DClass.GetField("mTestEnum", property);
			D_ASSERT(isPropertyReturned == true);
			D_ASSERT(property.IsValid() == true);
			D_ASSERT(property.GetFieldTypeSize() == sizeof(dooms::TestEnum_ReflectionTest));
			D_ASSERT(std::strcmp(dPrimitiveHelper::GetShortNamePointer(property.GetFieldVariableFullName()), "mTestEnum") == 0);

			dooms::TestStruct_ReflectionTest _TestStruct_ReflectionTest{};
			_TestStruct_ReflectionTest.mTestEnum = dooms::TestEnum_ReflectionTest::test2;
			
			dooms::TestEnum_ReflectionTest* currentValue = property.GetFieldValue<dooms::TestEnum_ReflectionTest>(&_TestStruct_ReflectionTest);
			D_ASSERT(*currentValue == dooms::TestEnum_ReflectionTest::test2);
		}

		{
			for(const dooms::DField& dfield : TestStruct_ReflectionTest_DClass.GetFieldList())
			{
				dooms::ui::PrintText("%s", dfield.GetFieldVariableFullName());
				dooms::ui::PrintText("%d", dfield.GetFieldTypeSize());
				dooms::ui::PrintText("%d", dfield.GetFieldOffset());
				dooms::ui::PrintText("is pointer : %s", (dfield.GetFieldQualifier() == dooms::DField::eProperyQualifier::POINTER) ? "yes" : "no");

			}
		}
	}



	{
		const dooms::DEnum eTestEnum_ReflectionTestDEnum = dooms::CreateDEnum<dooms::TestEnum_ReflectionTest>();

		D_ASSERT(std::strcmp(eTestEnum_ReflectionTestDEnum.GetValueName(1), "test1") == 0);
		D_ASSERT(std::strcmp(eTestEnum_ReflectionTestDEnum.GetValueName(3), "test2") == 0);
		D_ASSERT(std::strcmp(eTestEnum_ReflectionTestDEnum.GetValueName(5), "test3") == 0);
		D_ASSERT(std::strcmp(eTestEnum_ReflectionTestDEnum.GetValueName(444), "test4") == 0);

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
		auto mat4x4Name = db.GetName("math::_Matrix4x4<float>");
		auto mat4x4Type = db.GetType(mat4x4Name.hash);
		auto mat4x4tClass = mat4x4Type->AsTemplateType();

	}

	{
		auto transformName = db.GetName("dooms::Transform");
		auto transformType = db.GetType(transformName.hash);
		auto transformClass = transformType->AsClass();
		
	}

	{
		auto transform = dooms::CreateDClass<dooms::Transform>();

		dooms::DField property;
		const bool isPropertyReturned = transform.GetField("mTransformCoreData", property);
		D_ASSERT(isPropertyReturned == true);
		D_ASSERT(property.IsValid() == true);

		//property.GetPropertyValue<>()
	}



	{
		const dooms::DEnum eColorDEnum = dooms::CreateDEnum<dooms::graphics::eColor>();
		
		D_ASSERT(std::strcmp(eColorDEnum.GetValueName(0), "White") == 0);
		D_ASSERT(std::strcmp(eColorDEnum.GetValueName(1), "Black") == 0);
		D_ASSERT(std::strcmp(eColorDEnum.GetValueName(2), "Red") == 0);

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
