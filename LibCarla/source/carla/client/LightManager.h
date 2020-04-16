// Copyright (c) 2020 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "carla/Memory.h"
#include "carla/NonCopyable.h"

#include "carla/client/detail/Episode.h"
#include "carla/client/Light.h"
#include "carla/client/LightState.h"

namespace carla {
namespace client {

class LightManager
  : public EnableSharedFromThis<LightManager> {

public:

  LightManager();

  ~LightManager();

  LightManager(const LightManager&) = default;

  // TODO: remove
  void DebugFill() {
    SharedPtr<LightManager> lm = SharedPtr<LightManager>(this);
    geom::Location loc(0.0f,0.0f,0.0f);
    geom::Rotation rot;
    _lights_state.insert({66, LightState()});
    _lights_state.insert({67, LightState()});
    _lights.insert({66, Light(lm, loc, rot, 66)});
    _lights.insert({67, Light(lm, loc, rot, 67)});
  }

  void SetEpisode(detail::EpisodeProxy& episode);

  std::vector<Light> GetAllLights(LightGroup type = LightGroup::None) const;
  // TODO: std::vector<Light> GetAllLightsInRoad(RoadId id, LightGroup type = LightGroup::None);
  // TODO: std::vector<Light> GetAllLightsInDistance(Vec3 origin, float distance, LightGroup type = Light::LightType::None);

  void TurnOn(std::vector<Light>& lights);
  void TurnOff(std::vector<Light>& lights);
  void SetActive(std::vector<Light>& lights, std::vector<bool>& active);
  std::vector<bool> IsActive(std::vector<Light>& lights) const;
  std::vector<Light> GetTurnedOnLights(LightGroup type = LightGroup::None) const;
  std::vector<Light> GetTurnedOffLights(LightGroup type = LightGroup::None) const;

  void SetColor(std::vector<Light>& lights, Color color);
  void SetColor(std::vector<Light>& lights, std::vector<Color>& colors);
  std::vector<Color> GetColor(std::vector<Light>& lights) const;

  void SetIntensity(std::vector<Light>& lights, float intensity);
  void SetIntensity(std::vector<Light>& lights, std::vector<float>& intensities);
  std::vector<float> GetIntensity(std::vector<Light>& lights) const;

  void SetLightGroup(std::vector<Light>& lights, LightGroup group);
  void SetLightGroup(std::vector<Light>& lights, std::vector<LightGroup>& groups);
  std::vector<LightGroup> GetLightGroup(std::vector<Light>& lights) const;

  void SetLightState(std::vector<Light>& lights, LightState state);
  void SetLightState(std::vector<Light>& lights, std::vector<LightState>& states);
  std::vector<LightState> GetLightState(std::vector<Light>& lights) const;

  Color GetColor(LightId id) const;
  float GetIntensity(LightId id) const;
  LightState GetLightState(LightId id) const;
  LightGroup GetLightGroup(LightId id) const;
  bool IsActive(LightId id) const;

  void SetActive(LightId id, bool active);
  void SetColor(LightId id, Color color);
  void SetIntensity(LightId id, float intensity);
  void SetLightState(LightId id, const LightState& new_state);
  void SetLightGroup(LightId id, LightGroup group);

private:

  const LightState& RetrieveLightState(LightId id) const;

  void QueryLightsStateToServer();
  void UpdateServerLightsState();

  std::unordered_map<LightId, LightState> _lights_state;
  std::unordered_map<LightId, LightState> _lights_changes;
  std::unordered_map<LightId, Light> _lights;

  detail::EpisodeProxy _episode;

  LightState _state;
  size_t _on_tick_register_id = 0;
  bool _dirty = false;
};

} // namespace client
} // namespace carla
