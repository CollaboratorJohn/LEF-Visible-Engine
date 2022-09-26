#include "widgets.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>


// init global hash rect table
HashRect* HashRect::instance = NULL;

HashRect::HashRect() {}

HashRect::~HashRect() {}

HashRect* HashRect::getInstance() {
    if(!instance) {
        instance = new HashRect();
    }
    return instance;
}

std::string HashRect::hashStrGenerator() {
    auto uuid = boost::uuids::random_generator()();
    std::string suuid = boost::uuids::to_string(uuid);
    return suuid;
}

std::string HashRect::setRectHash(std::vector<CRectangle>::iterator rect) {
    std::string hash_id = hashStrGenerator();
    rect->setId(hash_id);
    hash_rect_map[hash_id] = rect;
    std::cout<<hash_id<<std::endl;
    return hash_id;
}

void HashRect::findRectHashInfo(std::string hash_id) {
    auto rect = hash_rect_map[hash_id];
    rect->printNames();
    auto pin = rect->getParent();
    pin->printNames();
    auto layer = pin->getParent();
    layer->printNames();
    auto cell = pin->getParent();
    cell->printNames();
}