#pragma once

#include <cassert>


#include <cstring>
#include <fstream>
#include <ios>

#include <DObject/DObject.h>
#include "Macros/Path.h"
#include "Macros/Assert.h"
#include "Macros/MacrosHelper.h"

#include "UI/PrintText.h"

#include "clReflectHelper.h"

namespace clReflectTest
{

	


	inline extern void test(clcpp::Database& db)
	{
		auto aName = db.GetName("doom");
		auto aNamespace = db.GetNamespace(aName.hash);
		auto cla = aNamespace->classes;

		for (size_t i = 0; i < cla.size; i++)
		{

			doom::ui::PrintText(cla.data[i]->name.text);
			doom::ui::PrintText("%d", cla.data[i]->size);
		}
	}
}
