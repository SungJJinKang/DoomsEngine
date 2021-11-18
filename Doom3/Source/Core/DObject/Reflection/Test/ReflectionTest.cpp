#include "ReflectionTest.h"

#include "Macros/Path.h"
#include "Macros/Assert.h"
#include "Macros/MacrosHelper.h"

#include "UI/PrintText.h"

#include <cstring>

#include "../clReflectHelper.h"

#include <Transform.h>

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
		auto propertyList = transform.GetProperty("mTransformCoreData", property);

	}

	{
		auto eColorName = db.GetName("dooms::graphics::eColor");
		auto eColorNameType = db.GetType(eColorName.hash);
		auto eColorEnum = eColorNameType->AsEnum();
		D_ASSERT(std::strcmp(eColorEnum->GetValueName(0), "dooms::graphics::eColor::White") == 0);
		D_ASSERT(std::strcmp(eColorEnum->GetValueName(1), "dooms::graphics::eColor::Black") == 0);
		D_ASSERT(std::strcmp(eColorEnum->GetValueName(2), "dooms::graphics::eColor::Red") == 0);
	}
	
	unsigned num;
	const clcpp::Type** type = db.GetTypes(num);

	for (size_t i = 0; i < num; i++)
	{
		dooms::ui::PrintText(type[i]->name.text);
	}
}
