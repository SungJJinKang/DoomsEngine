#include "ReflectionTest.h"

#include "Macros/Path.h"
#include "Macros/Assert.h"
#include "Macros/MacrosHelper.h"

#include "UI/PrintText.h"

#include <cstring>

#include "../clReflectHelper.h"

void clReflectTest::test(clcpp::Database& db)
{
	{
		auto DObjectName = db.GetName("dooms::DObject");
		auto DObjectType = db.GetType(DObjectName.hash);
		auto DObjectClass = DObjectType->AsClass();
	}

	{
		auto eColorName = db.GetName("dooms::graphics::eColor");
		auto eColorNameType = db.GetType(eColorName.hash);
		auto eColorEnum = eColorNameType->AsEnum();
		//D_ASSERT(std::strcmp(eColorEnum->GetValueName(0), "White") == 0);
		//D_ASSERT(std::strcmp(eColorEnum->GetValueName(1), "Black") == 0);
		//D_ASSERT(std::strcmp(eColorEnum->GetValueName(2), "Red") == 0);
	}

	
	unsigned num;
	const clcpp::Type** type = db.GetTypes(num);

	for (size_t i = 0; i < num; i++)
	{
		dooms::ui::PrintText(type[i]->name.text);
	}
}
