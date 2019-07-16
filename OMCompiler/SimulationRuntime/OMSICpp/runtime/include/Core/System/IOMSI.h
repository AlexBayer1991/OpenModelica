#pragma once

//OpenModelica Simulation Interface
#include <omsi.h>


class IOMSIAlgLoop;
class IOMSI
{
public:
	virtual omsi_status initialize_omsi_evaluate_functions(omsi_function_t* omsi_function) = 0;
	virtual omsi_status omsi_evaluateAll(omsi_function_t* simulation, const omsi_values* model_vars_and_params, void* data) = 0;
	virtual shared_ptr<IOMSIAlgLoop> getOMSIAlgLoop() = 0;
};

class IOMSIInitialize
{
public:
    virtual omsi_status initialize_omsi_initialize_functions(omsi_function_t* omsi_function) = 0;
    virtual omsi_status omsi_initializeAll(omsi_function_t* simulation, const omsi_values* model_vars_and_params,
                                           void* data) = 0;
};

class IOMSIAlgLoop
{
public:
	     
	virtual omsi_status initialize_instantiate_omsi_AlgSystem(omsi_algebraic_system_t* algSystem,  omsi_values* function_vars, omsi_values* pre_vars) = 0;
	virtual omsi_status evaluate_omsi_resFunction(omsi_function_t* this_function, const omsi_values* model_vars_and_params, void* res) = 0;
	virtual omsi_status evaluate_omsi_derivativeFunction(omsi_function_t* this_function, const omsi_values* model_vars_and_params, void* data) = 0;
};


class OMSICallBackWrapper {
public:
	static omsi_status evaluate(struct omsi_function_t*    this_function,
		const omsi_values*         read_only_vars_and_params,
		void*                      data)
	{

		return _omsu_system->omsi_evaluateAll(this_function, read_only_vars_and_params, data);
	};
	static omsi_status initialize(struct omsi_function_t*    this_function,
		const omsi_values*         read_only_vars_and_params,
		void*                      data)
	{
		return _omsu_initialize->omsi_initializeAll(this_function, read_only_vars_and_params,data);
	};
	static omsi_status evaluate_omsi_resFunction(struct omsi_function_t* this_function, const omsi_values* model_vars_and_params, void* res)
	{
		return _omsu_algloop->evaluate_omsi_resFunction(this_function, model_vars_and_params, res);
	};
	static omsi_status evaluate_omsi_derivativeMatFunc(struct omsi_function_t* this_function, const omsi_values* model_vars_and_params, void* data)
	{
		return _omsu_algloop->evaluate_omsi_derivativeFunction(this_function, model_vars_and_params, data);
	};
	static omsi_status setUpInitializeFunction(omsi_function_t* omsi_function)
	{
		return _omsu_initialize->initialize_omsi_initialize_functions(omsi_function);
	};
	static omsi_status setUpEvaluateFunction(omsi_function_t* omsi_function)
	{
		return _omsu_system->initialize_omsi_evaluate_functions(omsi_function);
	};
	static omsi_status setUpAlgLoopSystem(omsi_algebraic_system_t* algSystem,  omsi_values* function_vars, omsi_values* pre_vars)
	{
		return _omsu_algloop->initialize_instantiate_omsi_AlgSystem(algSystem, function_vars, pre_vars);
	};
	static void setOMSISystem(IOMSI& obj)
	{
		_omsu_system = &obj;
	}
	static void setOMSIInitialize(IOMSIInitialize& obj)
	{
		_omsu_initialize = &obj;
	}
	static void setOMSIAlgLoop(IOMSIAlgLoop& obj)
	{
		_omsu_algloop = &obj;
	}
	/*static omsi_status init_Algsystem_auf(struct omsi_algebraic_system_t* algSystem, const omsi_values* function_vars, const omsi_values* pre_vars) // Orientiert an OMSIC (neu)
	{
		return _omsu_system -> init_Algsystem_def(algSystem, function_vars, pre_vars);
	};
	static omsi_status init_resFunc_OMSIFunc_auf (struct omsi_function_t* this_function) // Orientiert an OMSIC (neu)
	{
		return _omsu_system -> init_resFunc_OMSIFunc_def(this_function);
	};
	static omsi_status init_resFunc_auf (struct omsi_function_t* this_function) // Orientiert an OMSIC (neu)
	{
		return _omsu_initialize -> init_resFunc_def(this_function);
	};
	static omsi_status init_derivativeMatFunc_OMSIFunc_auf (struct omsi_function_t* this_function) // Orientiert an OMSIC (neu)
	{
		return _omsu_initialize -> init_derivativeMatFunc_OMSIFunc_def(this_function);
	};
	static omsi_status init_derivativeMatFunc_auf(struct omsi_function_t* this_function, const omsi_values* model_vars_and_params, void* data) // Orientiert an OMSIC (neu)
	{
		return _omsu_initialize -> init_derivativeMatFunc_def(this_function, model_vars_and_params, data);
	};*/
private:
	static IOMSI* _omsu_system;
	static IOMSIInitialize* _omsu_initialize;
	static IOMSIAlgLoop* _omsu_algloop;
};
