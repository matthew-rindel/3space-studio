#ifndef DARKSTARDTSCONVERTER_DTS_RENDER_HPP
#define DARKSTARDTSCONVERTER_DTS_RENDER_HPP

#include <iterator>
#include <algorithm>
#include <utility>
#include <optional>
#include <map>
#include <unordered_map>
#include <set>
#include <memory_resource>
#include <glm/gtx/quaternion.hpp>

#include "renderable_shape.hpp"
#include "dts_structures.hpp"

struct instance_info
{
  using transform_set = std::pmr::set<std::variant<const darkstar::dts::shape::v2::transform*, const darkstar::dts::shape::v7::transform*, const darkstar::dts::shape::v8::transform*>>;
  std::unordered_map<std::int32_t, transform_set> node_indexes;
  std::unordered_map<std::int32_t, std::pmr::set<std::int32_t>> object_indexes;
};

class dts_renderable_shape : public renderable_shape
{
public:
  dts_renderable_shape(darkstar::dts::shape_variant shape)
    : shape(std::move(shape))
  {
  }

  std::vector<sequence_info> get_sequences(const std::vector<std::size_t>& detail_level_indexes) const override;

  std::vector<std::string> get_detail_levels() const override;
  void render_shape(shape_renderer& renderer, const std::vector<std::size_t>& detail_level_indexes, const std::vector<sequence_info>& sequences) const override;

private:
  darkstar::dts::shape_variant shape;
};


#endif//DARKSTARDTSCONVERTER_DTS_RENDER_HPP