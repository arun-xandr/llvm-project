set(LLVM_LINK_COMPONENTS
  DebugInfoDWARF
  )

add_llvm_component_library(LLVMDebugInfoGSYM
  DwarfTransformer.cpp
  Header.cpp
  FileWriter.cpp
  FunctionInfo.cpp
  GsymCreator.cpp
  GsymReader.cpp
  InlineInfo.cpp
  LineTable.cpp
  LookupResult.cpp
  Range.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/DebugInfo/GSYM
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/DebugInfo

  DEPENDS
  LLVMMC
  )
