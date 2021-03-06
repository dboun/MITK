/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <algorithm>
#include <mitkCoreServices.h>
#include <mitkIPropertyFilters.h>
#include <mitkProperties.h>
#include <mitkPropertyFilter.h>
#include <mitkTestingMacros.h>
#include <utility>

int mitkPropertyFiltersTest(int, char *[])
{
  MITK_TEST_BEGIN("mitkPropertyFiltersTest");

  mitk::IPropertyFilters *propertyFilters = mitk::CoreServices::GetPropertyFilters();
  MITK_TEST_CONDITION_REQUIRED(propertyFilters != nullptr, "Get property filters service");

  typedef std::map<std::string, mitk::BaseProperty::Pointer> PropertyMap;
  typedef PropertyMap::const_iterator PropertyMapConstIterator;

  PropertyMap propertyMap;
  propertyMap.insert(std::make_pair("propertyName1", mitk::BoolProperty::New().GetPointer()));
  propertyMap.insert(std::make_pair("propertyName2", mitk::BoolProperty::New().GetPointer()));
  propertyMap.insert(std::make_pair("propertyName3", mitk::BoolProperty::New().GetPointer()));

  mitk::PropertyFilter filter;
  filter.AddEntry("propertyName1", mitk::PropertyFilter::Whitelist);
  filter.AddEntry("propertyName2", mitk::PropertyFilter::Whitelist);

  mitk::PropertyFilter restrictedFilter;
  restrictedFilter.AddEntry("propertyName2", mitk::PropertyFilter::Blacklist);

  propertyFilters->AddFilter(filter);
  propertyFilters->AddFilter(restrictedFilter, "className");

  PropertyMap filteredPropertyMap = propertyFilters->ApplyFilter(propertyMap);
  PropertyMapConstIterator it1 = filteredPropertyMap.find("propertyName1");
  PropertyMapConstIterator it2 = filteredPropertyMap.find("propertyName2");
  PropertyMapConstIterator it3 = filteredPropertyMap.find("propertyName3");

  MITK_TEST_CONDITION(
    it1 != filteredPropertyMap.end() && it2 != filteredPropertyMap.end() && it3 == filteredPropertyMap.end(),
    "Apply global property filter");

  filteredPropertyMap = propertyFilters->ApplyFilter(propertyMap, "className");
  it1 = filteredPropertyMap.find("propertyName1");
  it2 = filteredPropertyMap.find("propertyName2");
  it3 = filteredPropertyMap.find("propertyName3");

  MITK_TEST_CONDITION(
    it1 != filteredPropertyMap.end() && it2 == filteredPropertyMap.end() && it3 == filteredPropertyMap.end(),
    "Apply restricted property filter (also respects global filter)");

  MITK_TEST_END();
}
