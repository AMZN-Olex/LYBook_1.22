#pragma once

/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <limits>
#include <AzCore/EBus/EBus.h>
#include <AzCore/Math/Uuid.h>
#include <AzCore/std/string/string.h>
#include <AzCore/std/smart_ptr/shared_ptr.h>
#include <AzCore/std/containers/vector.h>
#include <SceneAPI/SceneCore/SceneCoreConfiguration.h>

namespace AZ
{
    namespace SceneAPI
    {
        namespace Containers
        {
            class Scene;
        }
        namespace DataTypes
        {
            class IManifestObject;
        }
        namespace Events
        {
            class ManifestMetaInfo
                : public AZ::EBusTraits
            {
            public:
                static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

                struct CategoryRegistration
                {
                    AZStd::string m_categoryName;
                    AZ::Uuid m_categoryTargetGroupId;
                    int m_preferredOrder;

                    CategoryRegistration(const char* categoryName, const AZ::Uuid& categoryTargetId, int preferredOrder = std::numeric_limits<int>::max())
                        : m_categoryName(categoryName)
                        , m_categoryTargetGroupId(categoryTargetId)
                        , m_preferredOrder(preferredOrder)
                    {
                    }
                };
                using CategoryRegistrationList = AZStd::vector<CategoryRegistration>;
                using ModifiersList = AZStd::vector<AZ::Uuid>;

                SCENE_CORE_API ManifestMetaInfo();
                virtual ~ManifestMetaInfo() = 0;

                //! Gets a list of all the categories and the class identifiers that are listed for that category.
                SCENE_CORE_API virtual void GetCategoryAssignments(CategoryRegistrationList& categories, const Containers::Scene& scene);

                //! Gets the path to the icon associated with the given object.
                SCENE_CORE_API virtual void GetIconPath(AZStd::string& iconPath, const DataTypes::IManifestObject& target);

                //! Gets a list of a the modifiers (such as rules for  groups) that the target accepts.
                //! Note that updates to the target may change what modifiers can be accepted. For instance
                //! if a group only accepts a single rule of a particular type, calling this function a second time
                //! will not include the uuid of that rule.
                //! This method is called when the "Add Modifier" button is pressed in the FBX Settings Editor.
                SCENE_CORE_API virtual void GetAvailableModifiers(ModifiersList& modifiers, const Containers::Scene& scene, 
                    const DataTypes::IManifestObject& target);

                //! Initialized the given manifest object based on the scene. Depending on what other entries have been added
                //! to the manifest, an implementation of this function may decided that certain values should or shouldn't
                //! be added, such as not adding meshes to a group that already belong to another group.
                //! This method is always called each time a Group type of object is created in memory (e.g. When the user
                //! clicks the "Add another Mesh" or "Add another Actor" in the FBX Settings Editor). Overriders of this method
                //! should check the type of the \p target to decide to take action (e.g. add a Modifier) or do nothing.
                SCENE_CORE_API virtual void InitializeObject(const Containers::Scene& scene, DataTypes::IManifestObject& target);

                //! Called when an existing object is updated. This is not called when an object is initialized, which is handled,
                //! by InitializeObject, but a parent may still get the update. For instance adding or removing a rule will
                //! have this called for the parent group.
                //! @param scene The scene the object belongs to.
                //! @param target The object that's being updated. If this is null it refers to an update to the entire manifest, for
                //! when a group is deleted for instance.
                //! @param sender An optional argument to keep track of the object that called this function. This can be used if the
                //! same object that sends a message also handles the callback to avoid recursively updating.
                SCENE_CORE_API virtual void ObjectUpdated(const Containers::Scene& scene, const DataTypes::IManifestObject* target, void* sender = nullptr);
            };

            inline ManifestMetaInfo::~ManifestMetaInfo() = default;

            using ManifestMetaInfoBus = AZ::EBus<ManifestMetaInfo>;
        } // namespace Events
    } // namespace SceneAPI
} // namespace AZ
