/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/


#ifndef BERRYTESTCASE_H_
#define BERRYTESTCASE_H_

#include <cppunit/TestCase.h>

#include <org_blueberry_test_Export.h>

namespace berry {

class BERRY_TEST_EXPORT TestCase : public CppUnit::TestCase
{

public:

  TestCase(const QString& testName);

  /**
   * Sets up the fixture, for example, open a network connection.
   * This method is called before a test is executed.
   * The default implementation does nothing.
   * Subclasses may extend.
   */
  virtual void DoSetUp();

  /**
   * Tears down the fixture, for example, close a network connection.
   * This method is called after a test is executed.
   * The default implementation closes all test windows, processing events both before
   * and after doing so.
   * Subclasses may extend.
   */
  virtual void DoTearDown();

  /**
   * Clients should overwrite DoSetUp() instead of this method.
   */
  void setUp();

  /**
   * Clients should overwrite DoSetUp() instead of this method.
   */
  void tearDown();

protected:

  /**
   * Call this method in your unit test to enable detailed
   * output about leaking berry::Object instances.
   */
  void LeakDetailsOn();

  /**
   * Call this method to ignore leaking objects and to continue
   * with the unit tests.
   */
  void IgnoreLeakingObjects();

private:

  bool m_LeakDetails;
  bool m_IgnoreLeakage;

};

}

#endif /* BERRYTESTCASE_H_ */
