#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include <endpoint.pb.h>
#include <libfuzzer/libfuzzer_macro.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, std::size_t size) {
  if (size < 1) {
    return 0;
  }
  iroha::protocol::TxStatusRequest tx;
  if (protobuf_mutator::libfuzzer::LoadProtoInput(true, data, size, &tx)) {
    std::cout << "Execution successful" << std::endl;
  } else {
    std::cout << "Execution failed" << std::endl;
  }
  return 0;
}
