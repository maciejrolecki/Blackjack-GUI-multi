QT -= gui

TEMPLATE = lib
DEFINES += BLACKJACKCORE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/Card.cpp \
    Model/Croupier.cpp \
    Model/Deck.cpp \
    Model/Game.cpp \
    Model/Player.cpp \
    bj_json/game_info.cpp \
    bj_json/json_gen.cpp \
    bj_json/json_interpreter.cpp \
    bj_packet_ip/json_packet.cpp

HEADERS += \
    Model/Card.h \
    Model/Color.h \
    Model/Croupier.h \
    Model/Deck.h \
    Model/Game.h \
    Model/Player.h \
    Model/Value.h \
    bj_json/game_info.h \
    bj_json/json_gen.h \
    bj_json/json_interpreter.h \
    bj_packet_ip/json_packet.h \
    boost/optional.hpp \
    boost/optional/bad_optional_access.hpp \
    boost/optional/detail/experimental_traits.hpp \
    boost/optional/detail/old_optional_implementation.hpp \
    boost/optional/detail/optional_aligned_storage.hpp \
    boost/optional/detail/optional_config.hpp \
    boost/optional/detail/optional_factory_support.hpp \
    boost/optional/detail/optional_reference_spec.hpp \
    boost/optional/detail/optional_relops.hpp \
    boost/optional/detail/optional_swap.hpp \
    boost/optional/detail/optional_trivially_copyable_base.hpp \
    boost/optional/optional.hpp \
    boost/optional/optional_fwd.hpp \
    boost/optional/optional_io.hpp \
    boost/ptr_container/clone_allocator.hpp \
    boost/ptr_container/detail/associative_ptr_container.hpp \
    boost/ptr_container/detail/default_deleter.hpp \
    boost/ptr_container/detail/is_convertible.hpp \
    boost/ptr_container/detail/map_iterator.hpp \
    boost/ptr_container/detail/meta_functions.hpp \
    boost/ptr_container/detail/move.hpp \
    boost/ptr_container/detail/ptr_container_disable_deprecated.hpp \
    boost/ptr_container/detail/reversible_ptr_container.hpp \
    boost/ptr_container/detail/scoped_deleter.hpp \
    boost/ptr_container/detail/serialize_ptr_map_adapter.hpp \
    boost/ptr_container/detail/serialize_reversible_cont.hpp \
    boost/ptr_container/detail/serialize_xml_names.hpp \
    boost/ptr_container/detail/static_move_ptr.hpp \
    boost/ptr_container/detail/throw_exception.hpp \
    boost/ptr_container/detail/void_ptr_iterator.hpp \
    boost/ptr_container/exception.hpp \
    boost/ptr_container/indirect_fun.hpp \
    boost/ptr_container/nullable.hpp \
    boost/ptr_container/ptr_array.hpp \
    boost/ptr_container/ptr_circular_buffer.hpp \
    boost/ptr_container/ptr_container.hpp \
    boost/ptr_container/ptr_deque.hpp \
    boost/ptr_container/ptr_inserter.hpp \
    boost/ptr_container/ptr_list.hpp \
    boost/ptr_container/ptr_map.hpp \
    boost/ptr_container/ptr_map_adapter.hpp \
    boost/ptr_container/ptr_sequence_adapter.hpp \
    boost/ptr_container/ptr_set.hpp \
    boost/ptr_container/ptr_set_adapter.hpp \
    boost/ptr_container/ptr_unordered_map.hpp \
    boost/ptr_container/ptr_unordered_set.hpp \
    boost/ptr_container/ptr_vector.hpp \
    boost/ptr_container/serialize_ptr_array.hpp \
    boost/ptr_container/serialize_ptr_circular_buffer.hpp \
    boost/ptr_container/serialize_ptr_container.hpp \
    boost/ptr_container/serialize_ptr_deque.hpp \
    boost/ptr_container/serialize_ptr_list.hpp \
    boost/ptr_container/serialize_ptr_map.hpp \
    boost/ptr_container/serialize_ptr_set.hpp \
    boost/ptr_container/serialize_ptr_unordered_map.hpp \
    boost/ptr_container/serialize_ptr_unordered_set.hpp \
    boost/ptr_container/serialize_ptr_vector.hpp

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
