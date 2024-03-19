// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: order.proto

#include "order.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
constexpr makeOrderRequest::makeOrderRequest(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : goods_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , price_(0){}
struct makeOrderRequestDefaultTypeInternal {
  constexpr makeOrderRequestDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~makeOrderRequestDefaultTypeInternal() {}
  union {
    makeOrderRequest _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT makeOrderRequestDefaultTypeInternal _makeOrderRequest_default_instance_;
constexpr makeOrderResponse::makeOrderResponse(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : res_info_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , order_id_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , ret_code_(0){}
struct makeOrderResponseDefaultTypeInternal {
  constexpr makeOrderResponseDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~makeOrderResponseDefaultTypeInternal() {}
  union {
    makeOrderResponse _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT makeOrderResponseDefaultTypeInternal _makeOrderResponse_default_instance_;
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_order_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_order_2eproto = nullptr;
static const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* file_level_service_descriptors_order_2eproto[1];

const uint32_t TableStruct_order_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::makeOrderRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::makeOrderRequest, price_),
  PROTOBUF_FIELD_OFFSET(::makeOrderRequest, goods_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::makeOrderResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::makeOrderResponse, ret_code_),
  PROTOBUF_FIELD_OFFSET(::makeOrderResponse, res_info_),
  PROTOBUF_FIELD_OFFSET(::makeOrderResponse, order_id_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::makeOrderRequest)},
  { 8, -1, -1, sizeof(::makeOrderResponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_makeOrderRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_makeOrderResponse_default_instance_),
};

const char descriptor_table_protodef_order_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013order.proto\"0\n\020makeOrderRequest\022\r\n\005pri"
  "ce\030\001 \001(\005\022\r\n\005goods\030\002 \001(\t\"I\n\021makeOrderResp"
  "onse\022\020\n\010ret_code\030\001 \001(\005\022\020\n\010res_info\030\002 \001(\t"
  "\022\020\n\010order_id\030\003 \001(\t2;\n\005Order\0222\n\tmakeOrder"
  "\022\021.makeOrderRequest\032\022.makeOrderResponseB"
  "\003\200\001\001b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_order_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_order_2eproto = {
  false, false, 212, descriptor_table_protodef_order_2eproto, "order.proto", 
  &descriptor_table_order_2eproto_once, nullptr, 0, 2,
  schemas, file_default_instances, TableStruct_order_2eproto::offsets,
  file_level_metadata_order_2eproto, file_level_enum_descriptors_order_2eproto, file_level_service_descriptors_order_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_order_2eproto_getter() {
  return &descriptor_table_order_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_order_2eproto(&descriptor_table_order_2eproto);

// ===================================================================

class makeOrderRequest::_Internal {
 public:
};

makeOrderRequest::makeOrderRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:makeOrderRequest)
}
makeOrderRequest::makeOrderRequest(const makeOrderRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  goods_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    goods_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_goods().empty()) {
    goods_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_goods(), 
      GetArenaForAllocation());
  }
  price_ = from.price_;
  // @@protoc_insertion_point(copy_constructor:makeOrderRequest)
}

inline void makeOrderRequest::SharedCtor() {
goods_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  goods_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
price_ = 0;
}

makeOrderRequest::~makeOrderRequest() {
  // @@protoc_insertion_point(destructor:makeOrderRequest)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void makeOrderRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  goods_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void makeOrderRequest::ArenaDtor(void* object) {
  makeOrderRequest* _this = reinterpret_cast< makeOrderRequest* >(object);
  (void)_this;
}
void makeOrderRequest::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void makeOrderRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void makeOrderRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:makeOrderRequest)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  goods_.ClearToEmpty();
  price_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* makeOrderRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 price = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          price_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string goods = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_goods();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "makeOrderRequest.goods"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* makeOrderRequest::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:makeOrderRequest)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 price = 1;
  if (this->_internal_price() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_price(), target);
  }

  // string goods = 2;
  if (!this->_internal_goods().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_goods().data(), static_cast<int>(this->_internal_goods().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "makeOrderRequest.goods");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_goods(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:makeOrderRequest)
  return target;
}

size_t makeOrderRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:makeOrderRequest)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string goods = 2;
  if (!this->_internal_goods().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_goods());
  }

  // int32 price = 1;
  if (this->_internal_price() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_price());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData makeOrderRequest::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    makeOrderRequest::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*makeOrderRequest::GetClassData() const { return &_class_data_; }

void makeOrderRequest::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<makeOrderRequest *>(to)->MergeFrom(
      static_cast<const makeOrderRequest &>(from));
}


void makeOrderRequest::MergeFrom(const makeOrderRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:makeOrderRequest)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_goods().empty()) {
    _internal_set_goods(from._internal_goods());
  }
  if (from._internal_price() != 0) {
    _internal_set_price(from._internal_price());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void makeOrderRequest::CopyFrom(const makeOrderRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:makeOrderRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool makeOrderRequest::IsInitialized() const {
  return true;
}

void makeOrderRequest::InternalSwap(makeOrderRequest* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &goods_, lhs_arena,
      &other->goods_, rhs_arena
  );
  swap(price_, other->price_);
}

::PROTOBUF_NAMESPACE_ID::Metadata makeOrderRequest::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_order_2eproto_getter, &descriptor_table_order_2eproto_once,
      file_level_metadata_order_2eproto[0]);
}

// ===================================================================

class makeOrderResponse::_Internal {
 public:
};

makeOrderResponse::makeOrderResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:makeOrderResponse)
}
makeOrderResponse::makeOrderResponse(const makeOrderResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  res_info_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    res_info_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_res_info().empty()) {
    res_info_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_res_info(), 
      GetArenaForAllocation());
  }
  order_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    order_id_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_order_id().empty()) {
    order_id_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_order_id(), 
      GetArenaForAllocation());
  }
  ret_code_ = from.ret_code_;
  // @@protoc_insertion_point(copy_constructor:makeOrderResponse)
}

inline void makeOrderResponse::SharedCtor() {
res_info_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  res_info_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
order_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  order_id_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
ret_code_ = 0;
}

makeOrderResponse::~makeOrderResponse() {
  // @@protoc_insertion_point(destructor:makeOrderResponse)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void makeOrderResponse::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  res_info_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  order_id_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void makeOrderResponse::ArenaDtor(void* object) {
  makeOrderResponse* _this = reinterpret_cast< makeOrderResponse* >(object);
  (void)_this;
}
void makeOrderResponse::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void makeOrderResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void makeOrderResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:makeOrderResponse)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  res_info_.ClearToEmpty();
  order_id_.ClearToEmpty();
  ret_code_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* makeOrderResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 ret_code = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          ret_code_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string res_info = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_res_info();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "makeOrderResponse.res_info"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string order_id = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_order_id();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "makeOrderResponse.order_id"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* makeOrderResponse::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:makeOrderResponse)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 ret_code = 1;
  if (this->_internal_ret_code() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_ret_code(), target);
  }

  // string res_info = 2;
  if (!this->_internal_res_info().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_res_info().data(), static_cast<int>(this->_internal_res_info().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "makeOrderResponse.res_info");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_res_info(), target);
  }

  // string order_id = 3;
  if (!this->_internal_order_id().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_order_id().data(), static_cast<int>(this->_internal_order_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "makeOrderResponse.order_id");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_order_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:makeOrderResponse)
  return target;
}

size_t makeOrderResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:makeOrderResponse)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string res_info = 2;
  if (!this->_internal_res_info().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_res_info());
  }

  // string order_id = 3;
  if (!this->_internal_order_id().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_order_id());
  }

  // int32 ret_code = 1;
  if (this->_internal_ret_code() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_ret_code());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData makeOrderResponse::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    makeOrderResponse::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*makeOrderResponse::GetClassData() const { return &_class_data_; }

void makeOrderResponse::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<makeOrderResponse *>(to)->MergeFrom(
      static_cast<const makeOrderResponse &>(from));
}


void makeOrderResponse::MergeFrom(const makeOrderResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:makeOrderResponse)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_res_info().empty()) {
    _internal_set_res_info(from._internal_res_info());
  }
  if (!from._internal_order_id().empty()) {
    _internal_set_order_id(from._internal_order_id());
  }
  if (from._internal_ret_code() != 0) {
    _internal_set_ret_code(from._internal_ret_code());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void makeOrderResponse::CopyFrom(const makeOrderResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:makeOrderResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool makeOrderResponse::IsInitialized() const {
  return true;
}

void makeOrderResponse::InternalSwap(makeOrderResponse* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &res_info_, lhs_arena,
      &other->res_info_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &order_id_, lhs_arena,
      &other->order_id_, rhs_arena
  );
  swap(ret_code_, other->ret_code_);
}

::PROTOBUF_NAMESPACE_ID::Metadata makeOrderResponse::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_order_2eproto_getter, &descriptor_table_order_2eproto_once,
      file_level_metadata_order_2eproto[1]);
}

// ===================================================================

Order::~Order() {}

const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* Order::descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_order_2eproto);
  return file_level_service_descriptors_order_2eproto[0];
}

const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* Order::GetDescriptor() {
  return descriptor();
}

void Order::makeOrder(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                         const ::makeOrderRequest*,
                         ::makeOrderResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method makeOrder() not implemented.");
  done->Run();
}

void Order::CallMethod(const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
                             ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                             const ::PROTOBUF_NAMESPACE_ID::Message* request,
                             ::PROTOBUF_NAMESPACE_ID::Message* response,
                             ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(), file_level_service_descriptors_order_2eproto[0]);
  switch(method->index()) {
    case 0:
      makeOrder(controller,
             ::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ::makeOrderRequest*>(
                 request),
             ::PROTOBUF_NAMESPACE_ID::internal::DownCast<::makeOrderResponse*>(
                 response),
             done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::PROTOBUF_NAMESPACE_ID::Message& Order::GetRequestPrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::makeOrderRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::PROTOBUF_NAMESPACE_ID::MessageFactory::generated_factory()
          ->GetPrototype(method->input_type());
  }
}

const ::PROTOBUF_NAMESPACE_ID::Message& Order::GetResponsePrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::makeOrderResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::PROTOBUF_NAMESPACE_ID::MessageFactory::generated_factory()
          ->GetPrototype(method->output_type());
  }
}

Order_Stub::Order_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel)
  : channel_(channel), owns_channel_(false) {}
Order_Stub::Order_Stub(
    ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel,
    ::PROTOBUF_NAMESPACE_ID::Service::ChannelOwnership ownership)
  : channel_(channel),
    owns_channel_(ownership == ::PROTOBUF_NAMESPACE_ID::Service::STUB_OWNS_CHANNEL) {}
Order_Stub::~Order_Stub() {
  if (owns_channel_) delete channel_;
}

void Order_Stub::makeOrder(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                              const ::makeOrderRequest* request,
                              ::makeOrderResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0),
                       controller, request, response, done);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::makeOrderRequest* Arena::CreateMaybeMessage< ::makeOrderRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::makeOrderRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::makeOrderResponse* Arena::CreateMaybeMessage< ::makeOrderResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::makeOrderResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>