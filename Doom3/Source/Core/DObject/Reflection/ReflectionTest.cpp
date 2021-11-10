#include "ReflectionTest.h"

#include "Macros/Path.h"
#include "Macros/Assert.h"
#include "Macros/MacrosHelper.h"

#include "UI/PrintText.h"

#include "clReflectHelper.h"

void clReflectTest::test(clcpp::Database& db)
{
	auto DObjectName = db.GetName("dooms::DObject");
	auto DObjectType = db.GetType(DObjectName.hash);
	auto DObjectClass = DObjectType->AsClass();

	unsigned num;
	const clcpp::Type** type = db.GetTypes(num);

	for (size_t i = 0; i < num; i++)
	{
		dooms::ui::PrintText(type[i]->name.text);
	}
}
