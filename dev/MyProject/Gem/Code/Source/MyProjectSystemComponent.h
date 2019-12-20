#pragma once

#include <AzCore/Component/Component.h>

#include <MyProject/MyProjectBus.h>

namespace MyProject
{
    class MyProjectSystemComponent
        : public AZ::Component
        , protected MyProjectRequestBus::Handler
    {
    public:
        AZ_COMPONENT(MyProjectSystemComponent, "{1CDD814F-3AE2-44C3-AAE2-4B520E674455}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

    protected:
        ////////////////////////////////////////////////////////////////////////
        // MyProjectRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
