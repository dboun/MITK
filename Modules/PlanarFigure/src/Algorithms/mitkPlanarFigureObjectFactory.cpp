/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "mitkPlanarFigureObjectFactory.h"
#include "mitkPlanarFigureWriter.h"

#include "mitkCoreObjectFactory.h"

#include "mitkPlanarFigure.h"
#include "mitkPlanarFigureIOFactory.h"
#include "mitkPlanarFigureMapper2D.h"
#include "mitkPlanarFigureVtkMapper3D.h"
#include "mitkPlanarFigureWriterFactory.h"
#include "mitkVtkGLMapperWrapper.h"

typedef std::multimap<std::string, std::string> MultimapType;

mitk::PlanarFigureObjectFactory::PlanarFigureObjectFactory()
  : m_PlanarFigureIOFactory(PlanarFigureIOFactory::New().GetPointer()),
    m_PlanarFigureWriterFactory(PlanarFigureWriterFactory::New().GetPointer())
{
  static bool alreadyDone = false;
  if (!alreadyDone)
  {
    itk::ObjectFactoryBase::RegisterFactory(m_PlanarFigureIOFactory);
    itk::ObjectFactoryBase::RegisterFactory(m_PlanarFigureWriterFactory);

    m_FileWriters.push_back(PlanarFigureWriter::New().GetPointer());

    CreateFileExtensionsMap();

    alreadyDone = true;
  }
}

mitk::PlanarFigureObjectFactory::~PlanarFigureObjectFactory()
{
  itk::ObjectFactoryBase::UnRegisterFactory(m_PlanarFigureWriterFactory);
  itk::ObjectFactoryBase::UnRegisterFactory(m_PlanarFigureIOFactory);
}

mitk::Mapper::Pointer mitk::PlanarFigureObjectFactory::CreateMapper(mitk::DataNode *node, MapperSlotId id)
{
  mitk::Mapper::Pointer newMapper = nullptr;
  mitk::BaseData *data = node->GetData();

  if (dynamic_cast<PlanarFigure *>(data) != nullptr)
  {
    if (id == mitk::BaseRenderer::Standard2D)
    {
      newMapper = mitk::PlanarFigureMapper2D::New();
      newMapper->SetDataNode(node);
    }
    else if (id == mitk::BaseRenderer::Standard3D)
    {
      newMapper = mitk::PlanarFigureVtkMapper3D::New();
      newMapper->SetDataNode(node);
    }
  }

  return newMapper;
}

void mitk::PlanarFigureObjectFactory::SetDefaultProperties(mitk::DataNode *node)
{
  if (node == nullptr)
  {
    return;
  }

  mitk::DataNode::Pointer nodePointer = node;

  mitk::PlanarFigure::Pointer pf = dynamic_cast<mitk::PlanarFigure *>(node->GetData());
  if (pf.IsNotNull())
  {
    mitk::PlanarFigureMapper2D::SetDefaultProperties(node);
    mitk::PlanarFigureVtkMapper3D::SetDefaultProperties(node);
    node->AddProperty("color", mitk::ColorProperty::New(1.0, 1.0, 1.0), nullptr, true);
    node->AddProperty("opacity", mitk::FloatProperty::New(0.8), nullptr, true);
  }
}

const char *mitk::PlanarFigureObjectFactory::GetFileExtensions()
{
  return "";
}

mitk::CoreObjectFactoryBase::MultimapType mitk::PlanarFigureObjectFactory::GetFileExtensionsMap()
{
  return m_FileExtensionsMap;
}

const char *mitk::PlanarFigureObjectFactory::GetSaveFileExtensions()
{
  // return ";;Planar Figures (*.pf)";  // for mitk::PlanarFigure and derived classes
  std::string fileExtension;
  this->CreateFileExtensions(m_SaveFileExtensionsMap, fileExtension);
  return fileExtension.c_str();
};

mitk::CoreObjectFactoryBase::MultimapType mitk::PlanarFigureObjectFactory::GetSaveFileExtensionsMap()
{
  return m_SaveFileExtensionsMap;
}

void mitk::PlanarFigureObjectFactory::CreateFileExtensionsMap()
{
  m_FileExtensionsMap.insert(std::pair<std::string, std::string>("*.pf", "Planar Figure Files"));
  m_SaveFileExtensionsMap.insert(std::pair<std::string, std::string>("*.pf", "Planar Figure Files"));
}

void mitk::PlanarFigureObjectFactory::RegisterIOFactories()
{
}

struct RegisterPlanarFigureObjectFactory
{
  RegisterPlanarFigureObjectFactory() : m_Factory(mitk::PlanarFigureObjectFactory::New())
  {
    mitk::CoreObjectFactory::GetInstance()->RegisterExtraFactory(m_Factory);
  }

  ~RegisterPlanarFigureObjectFactory() { mitk::CoreObjectFactory::GetInstance()->UnRegisterExtraFactory(m_Factory); }
  mitk::PlanarFigureObjectFactory::Pointer m_Factory;
};

static RegisterPlanarFigureObjectFactory registerPlanarFigureObjectFactory;
