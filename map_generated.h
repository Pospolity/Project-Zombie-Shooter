// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MAP_TILEMAP_H_
#define FLATBUFFERS_GENERATED_MAP_TILEMAP_H_

#include "flatbuffers/flatbuffers.h"

namespace tileMap {

struct Vec2f;

struct Vec2i;

struct CollidingTile;
struct CollidingTileT;

struct Tile;
struct TileT;

struct Map;
struct MapT;

struct Layer;
struct LayerT;

struct MapList;
struct MapListT;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Vec2f FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;

 public:
  Vec2f() {
    memset(this, 0, sizeof(Vec2f));
  }
  Vec2f(float _x, float _y)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
};
FLATBUFFERS_STRUCT_END(Vec2f, 8);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Vec2i FLATBUFFERS_FINAL_CLASS {
 private:
  int32_t x_;
  int32_t y_;

 public:
  Vec2i() {
    memset(this, 0, sizeof(Vec2i));
  }
  Vec2i(int32_t _x, int32_t _y)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)) {
  }
  int32_t x() const {
    return flatbuffers::EndianScalar(x_);
  }
  int32_t y() const {
    return flatbuffers::EndianScalar(y_);
  }
};
FLATBUFFERS_STRUCT_END(Vec2i, 8);

struct CollidingTileT : public flatbuffers::NativeTable {
  typedef CollidingTile TableType;
  int8_t layerId;
  CollidingTileT()
      : layerId(-1) {
  }
};

struct CollidingTile FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef CollidingTileT NativeTableType;
  enum {
    VT_LAYERID = 4
  };
  int8_t layerId() const {
    return GetField<int8_t>(VT_LAYERID, -1);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_LAYERID) &&
           verifier.EndTable();
  }
  CollidingTileT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(CollidingTileT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<CollidingTile> Pack(flatbuffers::FlatBufferBuilder &_fbb, const CollidingTileT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct CollidingTileBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_layerId(int8_t layerId) {
    fbb_.AddElement<int8_t>(CollidingTile::VT_LAYERID, layerId, -1);
  }
  explicit CollidingTileBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  CollidingTileBuilder &operator=(const CollidingTileBuilder &);
  flatbuffers::Offset<CollidingTile> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CollidingTile>(end);
    return o;
  }
};

inline flatbuffers::Offset<CollidingTile> CreateCollidingTile(
    flatbuffers::FlatBufferBuilder &_fbb,
    int8_t layerId = -1) {
  CollidingTileBuilder builder_(_fbb);
  builder_.add_layerId(layerId);
  return builder_.Finish();
}

flatbuffers::Offset<CollidingTile> CreateCollidingTile(flatbuffers::FlatBufferBuilder &_fbb, const CollidingTileT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct TileT : public flatbuffers::NativeTable {
  typedef Tile TableType;
  uint16_t textureId;
  float rotation;
  TileT()
      : textureId(-1),
        rotation(0.0f) {
  }
};

struct Tile FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef TileT NativeTableType;
  enum {
    VT_TEXTUREID = 4,
    VT_ROTATION = 6
  };
  uint16_t textureId() const {
    return GetField<uint16_t>(VT_TEXTUREID, -1);
  }
  float rotation() const {
    return GetField<float>(VT_ROTATION, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint16_t>(verifier, VT_TEXTUREID) &&
           VerifyField<float>(verifier, VT_ROTATION) &&
           verifier.EndTable();
  }
  TileT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(TileT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Tile> Pack(flatbuffers::FlatBufferBuilder &_fbb, const TileT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct TileBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_textureId(uint16_t textureId) {
    fbb_.AddElement<uint16_t>(Tile::VT_TEXTUREID, textureId, -1);
  }
  void add_rotation(float rotation) {
    fbb_.AddElement<float>(Tile::VT_ROTATION, rotation, 0.0f);
  }
  explicit TileBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  TileBuilder &operator=(const TileBuilder &);
  flatbuffers::Offset<Tile> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Tile>(end);
    return o;
  }
};

inline flatbuffers::Offset<Tile> CreateTile(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint16_t textureId = -1,
    float rotation = 0.0f) {
  TileBuilder builder_(_fbb);
  builder_.add_rotation(rotation);
  builder_.add_textureId(textureId);
  return builder_.Finish();
}

flatbuffers::Offset<Tile> CreateTile(flatbuffers::FlatBufferBuilder &_fbb, const TileT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct MapT : public flatbuffers::NativeTable {
  typedef Map TableType;
  int8_t id;
  std::string name;
  std::string tileSheetPath;
  std::unique_ptr<Vec2i> tileSheetDimensions;
  std::unique_ptr<Vec2i> tileDimensions;
  std::unique_ptr<Vec2i> mapDimensions;
  int32_t numberOfLayers;
  std::vector<std::unique_ptr<LayerT>> layers;
  std::vector<std::unique_ptr<CollidingTileT>> collisionLayer;
  MapT()
      : id(0),
        numberOfLayers(0) {
  }
};

struct Map FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef MapT NativeTableType;
  enum {
    VT_ID = 4,
    VT_NAME = 6,
    VT_TILESHEETPATH = 8,
    VT_TILESHEETDIMENSIONS = 10,
    VT_TILEDIMENSIONS = 12,
    VT_MAPDIMENSIONS = 14,
    VT_NUMBEROFLAYERS = 16,
    VT_LAYERS = 18,
    VT_COLLISIONLAYER = 20
  };
  int8_t id() const {
    return GetField<int8_t>(VT_ID, 0);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::String *tileSheetPath() const {
    return GetPointer<const flatbuffers::String *>(VT_TILESHEETPATH);
  }
  const Vec2i *tileSheetDimensions() const {
    return GetStruct<const Vec2i *>(VT_TILESHEETDIMENSIONS);
  }
  const Vec2i *tileDimensions() const {
    return GetStruct<const Vec2i *>(VT_TILEDIMENSIONS);
  }
  const Vec2i *mapDimensions() const {
    return GetStruct<const Vec2i *>(VT_MAPDIMENSIONS);
  }
  int32_t numberOfLayers() const {
    return GetField<int32_t>(VT_NUMBEROFLAYERS, 0);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Layer>> *layers() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Layer>> *>(VT_LAYERS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<CollidingTile>> *collisionLayer() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<CollidingTile>> *>(VT_COLLISIONLAYER);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_ID) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.Verify(name()) &&
           VerifyOffset(verifier, VT_TILESHEETPATH) &&
           verifier.Verify(tileSheetPath()) &&
           VerifyField<Vec2i>(verifier, VT_TILESHEETDIMENSIONS) &&
           VerifyField<Vec2i>(verifier, VT_TILEDIMENSIONS) &&
           VerifyField<Vec2i>(verifier, VT_MAPDIMENSIONS) &&
           VerifyField<int32_t>(verifier, VT_NUMBEROFLAYERS) &&
           VerifyOffset(verifier, VT_LAYERS) &&
           verifier.Verify(layers()) &&
           verifier.VerifyVectorOfTables(layers()) &&
           VerifyOffset(verifier, VT_COLLISIONLAYER) &&
           verifier.Verify(collisionLayer()) &&
           verifier.VerifyVectorOfTables(collisionLayer()) &&
           verifier.EndTable();
  }
  MapT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(MapT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Map> Pack(flatbuffers::FlatBufferBuilder &_fbb, const MapT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct MapBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(int8_t id) {
    fbb_.AddElement<int8_t>(Map::VT_ID, id, 0);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Map::VT_NAME, name);
  }
  void add_tileSheetPath(flatbuffers::Offset<flatbuffers::String> tileSheetPath) {
    fbb_.AddOffset(Map::VT_TILESHEETPATH, tileSheetPath);
  }
  void add_tileSheetDimensions(const Vec2i *tileSheetDimensions) {
    fbb_.AddStruct(Map::VT_TILESHEETDIMENSIONS, tileSheetDimensions);
  }
  void add_tileDimensions(const Vec2i *tileDimensions) {
    fbb_.AddStruct(Map::VT_TILEDIMENSIONS, tileDimensions);
  }
  void add_mapDimensions(const Vec2i *mapDimensions) {
    fbb_.AddStruct(Map::VT_MAPDIMENSIONS, mapDimensions);
  }
  void add_numberOfLayers(int32_t numberOfLayers) {
    fbb_.AddElement<int32_t>(Map::VT_NUMBEROFLAYERS, numberOfLayers, 0);
  }
  void add_layers(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Layer>>> layers) {
    fbb_.AddOffset(Map::VT_LAYERS, layers);
  }
  void add_collisionLayer(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<CollidingTile>>> collisionLayer) {
    fbb_.AddOffset(Map::VT_COLLISIONLAYER, collisionLayer);
  }
  explicit MapBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  MapBuilder &operator=(const MapBuilder &);
  flatbuffers::Offset<Map> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Map>(end);
    return o;
  }
};

inline flatbuffers::Offset<Map> CreateMap(
    flatbuffers::FlatBufferBuilder &_fbb,
    int8_t id = 0,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::String> tileSheetPath = 0,
    const Vec2i *tileSheetDimensions = 0,
    const Vec2i *tileDimensions = 0,
    const Vec2i *mapDimensions = 0,
    int32_t numberOfLayers = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Layer>>> layers = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<CollidingTile>>> collisionLayer = 0) {
  MapBuilder builder_(_fbb);
  builder_.add_collisionLayer(collisionLayer);
  builder_.add_layers(layers);
  builder_.add_numberOfLayers(numberOfLayers);
  builder_.add_mapDimensions(mapDimensions);
  builder_.add_tileDimensions(tileDimensions);
  builder_.add_tileSheetDimensions(tileSheetDimensions);
  builder_.add_tileSheetPath(tileSheetPath);
  builder_.add_name(name);
  builder_.add_id(id);
  return builder_.Finish();
}

inline flatbuffers::Offset<Map> CreateMapDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int8_t id = 0,
    const char *name = nullptr,
    const char *tileSheetPath = nullptr,
    const Vec2i *tileSheetDimensions = 0,
    const Vec2i *tileDimensions = 0,
    const Vec2i *mapDimensions = 0,
    int32_t numberOfLayers = 0,
    const std::vector<flatbuffers::Offset<Layer>> *layers = nullptr,
    const std::vector<flatbuffers::Offset<CollidingTile>> *collisionLayer = nullptr) {
  return tileMap::CreateMap(
      _fbb,
      id,
      name ? _fbb.CreateString(name) : 0,
      tileSheetPath ? _fbb.CreateString(tileSheetPath) : 0,
      tileSheetDimensions,
      tileDimensions,
      mapDimensions,
      numberOfLayers,
      layers ? _fbb.CreateVector<flatbuffers::Offset<Layer>>(*layers) : 0,
      collisionLayer ? _fbb.CreateVector<flatbuffers::Offset<CollidingTile>>(*collisionLayer) : 0);
}

flatbuffers::Offset<Map> CreateMap(flatbuffers::FlatBufferBuilder &_fbb, const MapT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct LayerT : public flatbuffers::NativeTable {
  typedef Layer TableType;
  std::vector<std::unique_ptr<TileT>> tiles;
  LayerT() {
  }
};

struct Layer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef LayerT NativeTableType;
  enum {
    VT_TILES = 4
  };
  const flatbuffers::Vector<flatbuffers::Offset<Tile>> *tiles() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tile>> *>(VT_TILES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TILES) &&
           verifier.Verify(tiles()) &&
           verifier.VerifyVectorOfTables(tiles()) &&
           verifier.EndTable();
  }
  LayerT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(LayerT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Layer> Pack(flatbuffers::FlatBufferBuilder &_fbb, const LayerT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct LayerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_tiles(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tile>>> tiles) {
    fbb_.AddOffset(Layer::VT_TILES, tiles);
  }
  explicit LayerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  LayerBuilder &operator=(const LayerBuilder &);
  flatbuffers::Offset<Layer> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Layer>(end);
    return o;
  }
};

inline flatbuffers::Offset<Layer> CreateLayer(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tile>>> tiles = 0) {
  LayerBuilder builder_(_fbb);
  builder_.add_tiles(tiles);
  return builder_.Finish();
}

inline flatbuffers::Offset<Layer> CreateLayerDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<Tile>> *tiles = nullptr) {
  return tileMap::CreateLayer(
      _fbb,
      tiles ? _fbb.CreateVector<flatbuffers::Offset<Tile>>(*tiles) : 0);
}

flatbuffers::Offset<Layer> CreateLayer(flatbuffers::FlatBufferBuilder &_fbb, const LayerT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct MapListT : public flatbuffers::NativeTable {
  typedef MapList TableType;
  std::vector<std::unique_ptr<MapT>> maps;
  MapListT() {
  }
};

struct MapList FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef MapListT NativeTableType;
  enum {
    VT_MAPS = 4
  };
  const flatbuffers::Vector<flatbuffers::Offset<Map>> *maps() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Map>> *>(VT_MAPS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_MAPS) &&
           verifier.Verify(maps()) &&
           verifier.VerifyVectorOfTables(maps()) &&
           verifier.EndTable();
  }
  MapListT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(MapListT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<MapList> Pack(flatbuffers::FlatBufferBuilder &_fbb, const MapListT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct MapListBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_maps(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Map>>> maps) {
    fbb_.AddOffset(MapList::VT_MAPS, maps);
  }
  explicit MapListBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  MapListBuilder &operator=(const MapListBuilder &);
  flatbuffers::Offset<MapList> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<MapList>(end);
    return o;
  }
};

inline flatbuffers::Offset<MapList> CreateMapList(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Map>>> maps = 0) {
  MapListBuilder builder_(_fbb);
  builder_.add_maps(maps);
  return builder_.Finish();
}

inline flatbuffers::Offset<MapList> CreateMapListDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<Map>> *maps = nullptr) {
  return tileMap::CreateMapList(
      _fbb,
      maps ? _fbb.CreateVector<flatbuffers::Offset<Map>>(*maps) : 0);
}

flatbuffers::Offset<MapList> CreateMapList(flatbuffers::FlatBufferBuilder &_fbb, const MapListT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline CollidingTileT *CollidingTile::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new CollidingTileT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void CollidingTile::UnPackTo(CollidingTileT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = layerId(); _o->layerId = _e; };
}

inline flatbuffers::Offset<CollidingTile> CollidingTile::Pack(flatbuffers::FlatBufferBuilder &_fbb, const CollidingTileT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateCollidingTile(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<CollidingTile> CreateCollidingTile(flatbuffers::FlatBufferBuilder &_fbb, const CollidingTileT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const CollidingTileT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _layerId = _o->layerId;
  return tileMap::CreateCollidingTile(
      _fbb,
      _layerId);
}

inline TileT *Tile::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new TileT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Tile::UnPackTo(TileT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = textureId(); _o->textureId = _e; };
  { auto _e = rotation(); _o->rotation = _e; };
}

inline flatbuffers::Offset<Tile> Tile::Pack(flatbuffers::FlatBufferBuilder &_fbb, const TileT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateTile(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Tile> CreateTile(flatbuffers::FlatBufferBuilder &_fbb, const TileT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const TileT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _textureId = _o->textureId;
  auto _rotation = _o->rotation;
  return tileMap::CreateTile(
      _fbb,
      _textureId,
      _rotation);
}

inline MapT *Map::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new MapT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Map::UnPackTo(MapT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = id(); _o->id = _e; };
  { auto _e = name(); if (_e) _o->name = _e->str(); };
  { auto _e = tileSheetPath(); if (_e) _o->tileSheetPath = _e->str(); };
  { auto _e = tileSheetDimensions(); if (_e) _o->tileSheetDimensions = std::unique_ptr<Vec2i>(new Vec2i(*_e)); };
  { auto _e = tileDimensions(); if (_e) _o->tileDimensions = std::unique_ptr<Vec2i>(new Vec2i(*_e)); };
  { auto _e = mapDimensions(); if (_e) _o->mapDimensions = std::unique_ptr<Vec2i>(new Vec2i(*_e)); };
  { auto _e = numberOfLayers(); _o->numberOfLayers = _e; };
  { auto _e = layers(); if (_e) { _o->layers.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->layers[_i] = std::unique_ptr<LayerT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = collisionLayer(); if (_e) { _o->collisionLayer.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->collisionLayer[_i] = std::unique_ptr<CollidingTileT>(_e->Get(_i)->UnPack(_resolver)); } } };
}

inline flatbuffers::Offset<Map> Map::Pack(flatbuffers::FlatBufferBuilder &_fbb, const MapT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateMap(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Map> CreateMap(flatbuffers::FlatBufferBuilder &_fbb, const MapT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const MapT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _id = _o->id;
  auto _name = _o->name.empty() ? 0 : _fbb.CreateString(_o->name);
  auto _tileSheetPath = _o->tileSheetPath.empty() ? 0 : _fbb.CreateString(_o->tileSheetPath);
  auto _tileSheetDimensions = _o->tileSheetDimensions ? _o->tileSheetDimensions.get() : 0;
  auto _tileDimensions = _o->tileDimensions ? _o->tileDimensions.get() : 0;
  auto _mapDimensions = _o->mapDimensions ? _o->mapDimensions.get() : 0;
  auto _numberOfLayers = _o->numberOfLayers;
  auto _layers = _o->layers.size() ? _fbb.CreateVector<flatbuffers::Offset<Layer>> (_o->layers.size(), [](size_t i, _VectorArgs *__va) { return CreateLayer(*__va->__fbb, __va->__o->layers[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _collisionLayer = _o->collisionLayer.size() ? _fbb.CreateVector<flatbuffers::Offset<CollidingTile>> (_o->collisionLayer.size(), [](size_t i, _VectorArgs *__va) { return CreateCollidingTile(*__va->__fbb, __va->__o->collisionLayer[i].get(), __va->__rehasher); }, &_va ) : 0;
  return tileMap::CreateMap(
      _fbb,
      _id,
      _name,
      _tileSheetPath,
      _tileSheetDimensions,
      _tileDimensions,
      _mapDimensions,
      _numberOfLayers,
      _layers,
      _collisionLayer);
}

inline LayerT *Layer::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new LayerT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Layer::UnPackTo(LayerT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = tiles(); if (_e) { _o->tiles.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->tiles[_i] = std::unique_ptr<TileT>(_e->Get(_i)->UnPack(_resolver)); } } };
}

inline flatbuffers::Offset<Layer> Layer::Pack(flatbuffers::FlatBufferBuilder &_fbb, const LayerT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateLayer(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Layer> CreateLayer(flatbuffers::FlatBufferBuilder &_fbb, const LayerT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const LayerT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _tiles = _o->tiles.size() ? _fbb.CreateVector<flatbuffers::Offset<Tile>> (_o->tiles.size(), [](size_t i, _VectorArgs *__va) { return CreateTile(*__va->__fbb, __va->__o->tiles[i].get(), __va->__rehasher); }, &_va ) : 0;
  return tileMap::CreateLayer(
      _fbb,
      _tiles);
}

inline MapListT *MapList::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new MapListT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void MapList::UnPackTo(MapListT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = maps(); if (_e) { _o->maps.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->maps[_i] = std::unique_ptr<MapT>(_e->Get(_i)->UnPack(_resolver)); } } };
}

inline flatbuffers::Offset<MapList> MapList::Pack(flatbuffers::FlatBufferBuilder &_fbb, const MapListT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateMapList(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<MapList> CreateMapList(flatbuffers::FlatBufferBuilder &_fbb, const MapListT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const MapListT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _maps = _o->maps.size() ? _fbb.CreateVector<flatbuffers::Offset<Map>> (_o->maps.size(), [](size_t i, _VectorArgs *__va) { return CreateMap(*__va->__fbb, __va->__o->maps[i].get(), __va->__rehasher); }, &_va ) : 0;
  return tileMap::CreateMapList(
      _fbb,
      _maps);
}

inline const tileMap::MapList *GetMapList(const void *buf) {
  return flatbuffers::GetRoot<tileMap::MapList>(buf);
}

inline const tileMap::MapList *GetSizePrefixedMapList(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<tileMap::MapList>(buf);
}

inline bool VerifyMapListBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<tileMap::MapList>(nullptr);
}

inline bool VerifySizePrefixedMapListBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<tileMap::MapList>(nullptr);
}

inline void FinishMapListBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tileMap::MapList> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedMapListBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<tileMap::MapList> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<MapListT> UnPackMapList(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<MapListT>(GetMapList(buf)->UnPack(res));
}

}  // namespace tileMap

#endif  // FLATBUFFERS_GENERATED_MAP_TILEMAP_H_
