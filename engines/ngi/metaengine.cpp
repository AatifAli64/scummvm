/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "base/plugins.h"

#include "engines/advancedDetector.h"
#include "common/file.h"

#include "graphics/surface.h"

#include "ngi/ngi.h"
#include "ngi/detection.h"
#include "ngi/gameloader.h"

#include "backends/keymapper/action.h"
#include "backends/keymapper/keymapper.h"
#include "backends/keymapper/standard-actions.h"
#include "common/translation.h"
#include "common/system.h"

namespace NGI {

uint32 NGIEngine::getFeatures() const {
	return _gameDescription->desc.flags;
}

bool NGIEngine::isDemo() {
	return _gameDescription->desc.flags & ADGF_DEMO;
}

Common::Language NGIEngine::getLanguage() const {
	return _gameDescription->desc.language;
}

const char *NGIEngine::getGameId() const {
	return _gameDescription->desc.gameId;
}

int NGIEngine::getGameGID() const {
	return _gameDescription->gameId;
}

} // End of namspace Fullpipe

class NGIMetaEngine : public AdvancedMetaEngine<NGI::NGIGameDescription> {
public:
	const char *getName() const override {
		return "ngi";
	}

	bool hasFeature(MetaEngineFeature f) const override;

	int getMaximumSaveSlot() const override { return 99; }

	Common::Error createInstance(OSystem *syst, Engine **engine, const NGI::NGIGameDescription *desc) const override;
	Common::KeymapArray initKeymaps(const char *target) const override;
};

Common::KeymapArray NGIMetaEngine::initKeymaps(const char *target) const {
	using namespace Common;
	using namespace NGI;

	Keymap *engineKeyMap = new Keymap(Keymap::kKeymapTypeGame, "ngi-default", _("Default NGI keymap"));

	// Left Click (Standard Action)
	Action *act = new Action(kStandardActionLeftClick, _("Left Click"));
	act->setCustomEngineActionEvent(NGI::kActionLeftClick);
	act->addDefaultInputMapping("MOUSE_LEFT");
	act->addDefaultInputMapping("JOY_BUTTON0");
	engineKeyMap->addAction(act);

	// Right Click (Standard Action)
	act = new Action(kStandardActionRightClick, _("Right Click"));
	act->setCustomEngineActionEvent(NGI::kActionRightClick);
	act->addDefaultInputMapping("MOUSE_RIGHT");
	act->addDefaultInputMapping("JOY_BUTTON1");
	engineKeyMap->addAction(act);

	// Pause Game
	act = new Action("PAUSE", _("Pause Game"));
	act->setCustomEngineActionEvent(kActionPause);
	act->addDefaultInputMapping("SPACE");
	act->addDefaultInputMapping("JOY_BUTTON9");
	engineKeyMap->addAction(act);

	// Quit Game
	act = new Action("QUIT", _("Quit Game"));
	act->setCustomEngineActionEvent(kActionQuit);
	act->addDefaultInputMapping("q");
	act->addDefaultInputMapping("JOY_BUTTON8");
	engineKeyMap->addAction(act);

	// Move Up
	act = new Action("MOVE_UP", _("Move Up"));
	act->setCustomEngineActionEvent(kActionMoveUp);
	act->addDefaultInputMapping("UP");
	act->addDefaultInputMapping("JOY_UP");
	engineKeyMap->addAction(act);

	// Move Down
	act = new Action("MOVE_DOWN", _("Move Down"));
	act->setCustomEngineActionEvent(kActionMoveDown);
	act->addDefaultInputMapping("DOWN");
	act->addDefaultInputMapping("JOY_DOWN");
	engineKeyMap->addAction(act);

	// Move Left
	act = new Action("MOVE_LEFT", _("Move Left"));
	act->setCustomEngineActionEvent(kActionMoveLeft);
	act->addDefaultInputMapping("LEFT");
	act->addDefaultInputMapping("JOY_LEFT");
	engineKeyMap->addAction(act);

	// Move Right
	act = new Action("MOVE_RIGHT", _("Move Right"));
	act->setCustomEngineActionEvent(kActionMoveRight);
	act->addDefaultInputMapping("RIGHT");
	act->addDefaultInputMapping("JOY_RIGHT");
	engineKeyMap->addAction(act);

	return Keymap::arrayOf(engineKeyMap);
}

bool NGIMetaEngine::hasFeature(MetaEngineFeature f) const {
	return checkExtendedSaves(f) || (f == kSupportsLoadingDuringStartup);
}

bool NGI::NGIEngine::hasFeature(EngineFeature f) const {
	return
		(f == kSupportsReturnToLauncher) ||
		(f == kSupportsLoadingDuringRuntime) ||
		(f == kSupportsSavingDuringRuntime);
}


Common::Error NGIMetaEngine::createInstance(OSystem *syst, Engine **engine, const NGI::NGIGameDescription *desc) const {
	*engine = new NGI::NGIEngine(syst,desc);
	return Common::kNoError;
}

#if PLUGIN_ENABLED_DYNAMIC(NGI)
	REGISTER_PLUGIN_DYNAMIC(NGI, PLUGIN_TYPE_ENGINE, NGIMetaEngine);
#else
	REGISTER_PLUGIN_STATIC(NGI, PLUGIN_TYPE_ENGINE, NGIMetaEngine);
#endif
