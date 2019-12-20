
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include <MyProjectSystemComponent.h>

namespace MyProject
{
    class MyProjectModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(MyProjectModule, "{90E07895-5FC8-437D-BE0D-73573FE68EC1}", AZ::Module);
        AZ_CLASS_ALLOCATOR(MyProjectModule, AZ::SystemAllocator, 0);

        MyProjectModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MyProjectSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyProjectSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(MyProject_69f5f91547dc40beb5d3582f8e8e35e4, MyProject::MyProjectModule)
