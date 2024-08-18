#pragma once

#include "iress_tr_table.h"
#include "iress_tr_defines.h"
#include <map>

class iress_tr_command_handler
{

private:
    // Controller class has 1 instance of Table
    iress_tr_table m_table;

    // Command handler table structure declaration
    struct IRESS_TR_COMMAND_HANDLER_TABLE {
        long        command_id;
        void (iress_tr_command_handler::*func_p) (const std::map<IRES_TR_NODE_ID, LONG>& );
    };

    // Command Handler table defines
    static const IRESS_TR_COMMAND_HANDLER_TABLE				s_iress_tr_command_handler_table_[];
    static const UINT   							        s_iress_tr_command_handler_table_size_;

public:
    iress_tr_command_handler();
    ~iress_tr_command_handler();

    //--------------------------------------------------------------
    //! place function.
    //!		@param[in]		command id			    robot's command. 
    //!		@param[in]		request					request parameters (input node). 
    //--------------------------------------------------------------
    //! @details
    //!     the main interface to the lower modules.
    //!     perform processing of the command ids from the application and dispatch
    //!     to the appropriate handler function of the received command.
    //--------------------------------------------------------------
    void iress_tr_command_handler_facade(IRES_TR_COMMAND_ID command_id, const std::map<IRES_TR_NODE_ID, LONG>& request);

public:
    // Handler declarations

    //--------------------------------------------------------------
    //! place command handler.
    //!		@param[in]		request					request parameters (input node/ addinfo). 
    //--------------------------------------------------------------
    //! @details
    //--------------------------------------------------------------
    void handler_place  (const std::map<IRES_TR_NODE_ID, LONG >& request);

    //--------------------------------------------------------------
    //! move command handler.
    //!		@param[in]		request					request parameters (input node/ addinfo). 
    //--------------------------------------------------------------
    //! @details
    //--------------------------------------------------------------
    void handler_move   (const std::map<IRES_TR_NODE_ID, LONG >& request);

    //--------------------------------------------------------------
    //! left command handler.
    //!		@param[in]		request				    request parameters (input node/ addinfo). 
    //--------------------------------------------------------------
    //! @details
    //--------------------------------------------------------------
    void handler_left   (const std::map<IRES_TR_NODE_ID, LONG >& request);

    //--------------------------------------------------------------
    //! place command handler.
    //!		@param[in]		request					request parameters (input node/ addinfo). 
    //--------------------------------------------------------------
    //! @details
    //--------------------------------------------------------------
    void handler_right  (const std::map<IRES_TR_NODE_ID, LONG >& request);

    //--------------------------------------------------------------
    //! place command handler.
    //!		@param[in]		request					request parameters (input node/ addinfo). 
    //--------------------------------------------------------------
    //! @details
    //--------------------------------------------------------------
    void handler_report (const std::map<IRES_TR_NODE_ID, LONG >& request);

};

