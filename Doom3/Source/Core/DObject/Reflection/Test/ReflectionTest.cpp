#include "ReflectionTest.h"

#include "Macros/Path.h"
#include "Macros/Assert.h"
#include "Macros/MacrosHelper.h"

#include "UI/PrintText.h"

#include <cstring>

#include "../clReflectHelper.h"

#include <Transform.h>

#include "../ReflectionType/DEnum.h"
#include "Graphics/Color.h"


namespace reflectionTest
{
	
}

void clReflectTest::test(clcpp::Database& db)
{
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

		dooms::DProperty property;
		const bool isPropertyReturned = transform.GetProperty("mTransformCoreData", property);
		D_ASSERT(isPropertyReturned == true);
		D_ASSERT(property.IsValid() == true);
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
