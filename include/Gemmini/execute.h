#include <Gemmini/gemmini_base.h>

namespace ilang {

namespace Gemmini {

enum dataflow_t {OS, WS};

enum compute_child_states {INACTIVE, PRELOAD, INITIALIZE_WS_RESULTS, WS_COMPUTE, OS_COMPUTE, OUTPUT_RESULTS};

struct execute_statevars_t {
    ExprRef dataflow = (ExprRef) NULL;
    ExprRef act = (ExprRef) NULL;
    ExprRef sys_shift = (ExprRef) NULL;
    ExprRef sys_acc_shift = (ExprRef) NULL;
    ExprRef a_transpose = (ExprRef) NULL;
    ExprRef b_transpose = (ExprRef) NULL;
    ExprRef c_stride = (ExprRef) NULL;
    ExprRef a_stride = (ExprRef) NULL;

    ExprRef preload_sp_addr = (ExprRef) NULL;
    ExprRef output_sp_addr = (ExprRef) NULL;
    ExprRef preload_cols = (ExprRef) NULL;
    ExprRef preload_rows = (ExprRef) NULL;
    ExprRef output_cols = (ExprRef) NULL;
    ExprRef output_rows = (ExprRef) NULL;

    ExprRef systolic_array = (ExprRef) NULL;
    ExprRef ws_results = (ExprRef) NULL;
    ExprRef child_state = (ExprRef) NULL;

    ExprRef i =(ExprRef) NULL;
    ExprRef j = (ExprRef) NULL;
    ExprRef k =(ExprRef) NULL;

};

struct tile_compute_args_t {
    ExprRef addr = (ExprRef) NULL;
    ExprRef rows = (ExprRef) NULL;
    ExprRef cols = (ExprRef) NULL;
};

struct compute_args_t {
    tile_compute_args_t a;
    tile_compute_args_t bd;
};

void DefineExecuteStatevars(Ila& m, execute_statevars_t &execute_statevars);
void DefineMatmulPreload(Ila& m, command_t& command, execute_statevars_t &execute_statevars);
void DefineConfigExecute(Ila& m, command_t& command, execute_statevars_t &execute_statevars);
void DefineMatmulPreload(Ila& m, command_t& command, execute_statevars_t &execute_statevars);
void DefineComputeMatmul(Ila& m, command_t& command, execute_statevars_t &execute_statevars, 
                        gemmini_memory_t memory);


void DefineComputeMatmulInstruction(Ila& m, command_t& command, execute_statevars_t &execute_statevars,
                                    gemmini_memory_t memory, bool preload, dataflow_t dataflow);
std:: string _BuildComputeMatmulInstrName(bool preload, dataflow_t dataflow);

void DefinePreload(Ila &child, ExprRef &spad, execute_statevars_t &execute_statevars);
void DefineInitializeWSResults(Ila &child, ExprRef &spad, execute_statevars_t &execute_statevars, tile_compute_args_t &bd_args);
void DefineMatmulWS(Ila &child, ExprRef &spad, execute_statevars_t &execute_statevars, compute_args_t &compute_args);
void DefineMatmulOS(Ila &child, ExprRef &spad, execute_statevars_t &execute_statevars, compute_args_t &compute_args);

ExprRef _GetTileAElmt(ExprRef &spad, execute_statevars_t &execute_statevars, tile_compute_args_t &a_args, ExprRef &i_bv, ExprRef &k_bv);

void DefineStoreOutputChild(Ila &m, command_t &command, execute_statevars_t &execute_statevars, gemmini_memory_t &memory);
void DefineStoreOutputInstruction(Ila &store_output, command_t &command, execute_statevars_t &execute_statevars, 
                        gemmini_memory_t &memory, dataflow_t const &dataflow, bool acc_address, bool accumulate_output);
std::string _BuildStoreOutputInstrName(dataflow_t const &dataflow, bool acc_address, bool accumulate_output);
ExprRef _RoundingRightShift(ExprRef const &x, ExprRef const &shift);

} // namespace Gemmini

} // namespace ilang