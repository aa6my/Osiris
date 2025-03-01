#pragma once

#include <algorithm>

#include <CS2/Classes/Panorama.h>
#include <CS2/Constants/SoundNames.h>
#include <FeatureHelpers/HudInWorldPanels.h>
#include <FeatureHelpers/HudInWorldPanelFactory.h>
#include <FeatureHelpers/PanoramaTransformations.h>
#include <FeatureHelpers/Sound/SoundVisualizationFeature.h>
#include <FeatureHelpers/Sound/SoundWatcher.h>
#include <FeatureHelpers/TogglableFeature.h>
#include <FeatureHelpers/WorldToClipSpaceConverter.h>
#include <GameClasses/Panel.h>
#include <GameClasses/PanoramaUiEngine.h>
#include <Helpers/HudProvider.h>
#include <Helpers/PanoramaTransformFactory.h>
#include <Hooks/ViewRenderHook.h>

#include "FootstepVisualizer.h"

struct BombPlantPanels {
    [[nodiscard]] static cs2::CPanel2D* createContainerPanel(const HudInWorldPanelFactory& inWorldFactory) noexcept
    {
        return inWorldFactory.createPanel("BombPlantContainer", HudInWorldPanelZOrder::BombPlant);
    }

    static void createContentPanels(cs2::CUIPanel& containerPanel) noexcept
    {
        for (std::size_t i = 0; i < kMaxNumberOfPanels; ++i) {
            PanoramaUiEngine::runScript(&containerPanel,
                R"(
(function() {
var bombPlantPanel = $.CreatePanel('Panel', $.GetContextPanel().FindChildInLayoutFile("BombPlantContainer"), '', {
  style: 'width: 100px; height: 100px; x: -50px; y: -100px; transform-origin: 50% 100%;'
});

$.CreatePanel('Image', bombPlantPanel, '', {
  src: "s2r://panorama/images/icons/ui/chatwheel_bombat.svg",
  style: "horizontal-align: center; vertical-align: bottom; img-shadow: 0px 0px 1px 3 #000000;",
  textureheight: "64"
});
})();)", "", 0);
        }
    }

    static constexpr auto kMaxNumberOfPanels = 5;
};

using BombPlantVisualizer = SoundVisualizationFeature<BombPlantPanels, BombPlantSound>;
