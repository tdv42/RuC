/*
 *	Copyright 2014 Andrey Terekhov
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 */

#include "codes.h"
#include <string.h>
#include "errors.h"
#include "nodes.h"
#include "old_tree.h"
#include "uniio.h"
#include "uniprinter.h"


#define MAX_ELEM_SIZE	32
#define INDENT			"  "


size_t elem_get_name(const item_t elem, const size_t num, char *const buffer)
{
	if (buffer == NULL)
	{
		return 0;
	}

	size_t argc = 0;
	int was_switch = 0;

	switch (elem)
	{
		case ND_FUNC_DEF:
			argc = 2;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TFuncdef");
					break;
				case 1:
					sprintf(buffer, "funcn");
					break;
				case 2:
					sprintf(buffer, "maxdispl");
					break;
			}
			break;
		case ND_DECL_ARR:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TDeclarr");
					break;
				case 1:
					sprintf(buffer, "N");
					break;
			}
			break;
		case ND_DECL_ID:
			argc = 7;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TDeclid");
					break;
				case 1:
					sprintf(buffer, "displ");
					break;
				case 2:
					sprintf(buffer, "eltype");
					break;
				case 3:
					sprintf(buffer, "N");
					break;
				case 4:
					sprintf(buffer, "all");
					break;
				case 5:
					sprintf(buffer, "iniproc");
					break;
				case 6:
					sprintf(buffer, "usual");
					break;
				case 7:
					sprintf(buffer, "instuct");
					break;
			}
			break;
		case ND_STRING:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TString");
					break;
				case 1:
					sprintf(buffer, "n");
					break;
			}
			break;
		case ND_STRINGD:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TStringd");
					break;
				case 1:
					sprintf(buffer, "n");
					break;
			}
			break;
		case ND_CONDITIONAL:
			sprintf(buffer, "TCondexpr");
			break;
		case ND_BLOCK:
			sprintf(buffer, "TBegin");
			break;
		case ND_BLOCK_END:
			sprintf(buffer, "TEnd");
			break;
		case ND_ARRAY_INIT:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TBeginit");
					break;
				case 1:
					sprintf(buffer, "n");
					break;
			}
			break;
		case ND_STRUCT_INIT:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TStructinit");
					break;
				case 1:
					sprintf(buffer, "n");
					break;
			}
			break;
		case ND_IF:
			argc = 1;
			sprintf(buffer, "TIf");
			break;
		case ND_WHILE:
			sprintf(buffer, "TWhile");
			break;
		case ND_DO:
			sprintf(buffer, "TDo");
			break;
		case ND_FOR:
			argc = 4;
			sprintf(buffer, "TFor");
			break;
		case ND_SWITCH:
			sprintf(buffer, "TSwitch");
			break;
		case ND_CASE:
			sprintf(buffer, "TCase");
			break;
		case ND_DEFAULT:
			sprintf(buffer, "TDefault");
			break;
		case ND_BREAK:
			sprintf(buffer, "TBreak");
			break;
		case ND_CONTINUE:
			sprintf(buffer, "TContinue");
			break;
		case ND_RETURN_VOID:
			sprintf(buffer, "TReturn");
			break;
		case ND_RETURN_VAL:
			argc = 1;
			sprintf(buffer, "TReturnval");
			break;
		case ND_GOTO:
			argc = 1;
			sprintf(buffer, "TGoto");
			break;
		case ND_IDENT:
			argc = 1;
			sprintf(buffer, "TIdent");
			break;
		case ND_IDENTTOVAL:
			argc = 1;
			sprintf(buffer, "TIdenttoval");
			break;
		case ND_IDENTTOVALD:
			argc = 1;
			sprintf(buffer, "TIdenttovald");
			break;
		case ND_IDENTTOADDR:
			argc = 1;
			sprintf(buffer, "TIdenttoaddr");
			break;
		case ND_ADDRTOVAL:
			sprintf(buffer, "TAddrtoval");
			break;
		case ND_ADDRTOVALD:
			sprintf(buffer, "TAddrtovald");
			break;
		case ND_EXPRESSION_END:
			sprintf(buffer, "TExprend");
			break;
		case ND_CONST:
			argc = 1;
			sprintf(buffer, "TConst");
			break;
		case ND_CONSTD:
			argc = 2;
			sprintf(buffer, "TConstd");
		break;
		case ND_SLICEIDENT:
			argc = 2;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TSliceident");
					break;
				case 1:
					sprintf(buffer, "displ");
					break;
				case 2:
					sprintf(buffer, "type");
					break;
			}
			break;
		case ND_SLICE:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TSlice");
					break;
				case 1:
					sprintf(buffer, "elem_type");
					break;
			}
			break;
		case ND_SELECT:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "TSelect");
					break;
				case 1:
					sprintf(buffer, "displ");
					break;
			}
			break;
		case ND_NULL:
			sprintf(buffer, "NOP");
			break;
		case ND_ADLOGAND:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "ADLOGAND");
					break;
				case 1:
					sprintf(buffer, "addr");
					break;
			}
			break;
		case ND_ADLOGOR:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "ADLOGOR");
					break;
				case 1:
					sprintf(buffer, "addr");
					break;
			}
			break;
		case ND_COPY00:
			argc = 3;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "COPY00");
					break;
				case 1:
					sprintf(buffer, "displleft");
					break;
				case 2:
					sprintf(buffer, "displright");
					break;
				case 3:
					sprintf(buffer, "length");
					break;
			}
			break;
		case ND_COPY01:
			argc = 2;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "COPY01");
					break;
				case 1:
					sprintf(buffer, "displleft");
					break;
				case 2:
					sprintf(buffer, "length");
					break;
			}
			break;
		case ND_COPY10:
			argc = 2;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "COPY10");
					break;
				case 1:
					sprintf(buffer, "displright");
					break;
				case 2:
					sprintf(buffer, "length");
					break;
			}
			break;
		case ND_COPY11:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "COPY11");
					break;
				case 1:
					sprintf(buffer, "length");
					break;
			}
			break;
		case ND_COPY0ST:
			argc = 2;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "COPY0ST");
					break;
				case 1:
					sprintf(buffer, "displleft");
					break;
				case 2:
					sprintf(buffer, "length");
					break;
			}
			break;
		case ND_COPY1ST:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "COPY1ST");
					break;
				case 1:
					sprintf(buffer, "length");
					break;
			}
			break;
		case ND_COPY0STASS:
			argc = 2;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "COPY0STASS");
					break;
				case 1:
					sprintf(buffer, "displleft");
					break;
				case 2:
					sprintf(buffer, "length");
					break;
			}
			break;
		case ND_COPY1STASS:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "COPY1STASS");
					break;
				case 1:
					sprintf(buffer, "length");
					break;
			}
			break;
		case ND_COPYST:
			argc = 3;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "COPYST");
					break;
				case 1:
					sprintf(buffer, "displ");
					break;
				case 2:
					sprintf(buffer, "length");
					break;
				case 3:
					sprintf(buffer, "length1");
					break;
			}
			break;

		case ND_CALL1:
			argc = 1;
			sprintf(buffer, "TCall1");
			break;
		case ND_CALL2:
			argc = 1;
			sprintf(buffer, "TCall2");
			break;
		case ND_LABEL:
			argc = 1;
			sprintf(buffer, "TLabel");
			break;
		case ND_DECL_STRUCT:
			argc = 1;
			sprintf(buffer, "TStructbeg");
			break;
		case ND_DECL_STRUCT_END:
			argc = 1;
			sprintf(buffer, "TStructend");
			break;
		case ND_PRINT:
			argc = 1;
			sprintf(buffer, "TPrint");
			break;
		case ND_PRINTID:
			argc = 1;
			sprintf(buffer, "TPrintid");
			break;
		case ND_PRINTF:
			argc = 1;
			sprintf(buffer, "TPrintf");
			break;
		case ND_GETID:
			argc = 1;
			sprintf(buffer, "TGetid");
			break;
		case ND_CREATE:
			sprintf(buffer, "TCREATE");
			break;
		case ND_CREATEDIRECT:
			sprintf(buffer, "TCREATEDIRECT");
			break;
		case ND_EXIT:
			sprintf(buffer, "TEXIT");
			break;
		case ND_EXITDIRECT:
			sprintf(buffer, "TEXITDIRECT");
			break;
		case ND_MSG_SEND:
			sprintf(buffer, "TMSGSEND");
			break;
		case ND_MSG_RECEIVE:
			sprintf(buffer, "TMSGRECEIVE");
			break;
		case ND_JOIN:
			sprintf(buffer, "TJOIN");
			break;
		case ND_SLEEP:
			sprintf(buffer, "TSLEEP");
			break;
		case ND_SEMCREATE:
			sprintf(buffer, "TSEMCREATE");
			break;
		case ND_SEMWAIT:
			sprintf(buffer, "TSEMWAIT");
			break;
		case ND_SEMPOST:
			sprintf(buffer, "TSEMPOST");
			break;
		case ND_INIT:
			sprintf(buffer, "INITC");
			break;
		case ND_DESTROY:
			sprintf(buffer, "DESTROYC");
			break;
		case ND_GETNUM:
			sprintf(buffer, "GETNUMC");
			break;

		case IC_PRINT:
			argc = 1;
			sprintf(buffer, "PRINT");
			break;
		case IC_PRINTID:
			argc = 1;
			sprintf(buffer, "PRINTID");
			break;
		case IC_PRINTF:
			argc = 1;
			sprintf(buffer, "PRINTF");
			break;
		case IC_GETID:
			argc = 1;
			sprintf(buffer, "GETID");
			break;
		case IC_INIT:
			sprintf(buffer, "TINIT");
			break;
		case IC_DESTROY:
			sprintf(buffer, "TDESTROY");
			break;

		case ND_ABS:
			sprintf(buffer, "ABS");
			break;
		case ND_ABSI:
			sprintf(buffer, "ABSI");
			break;
		case ND_SQRT:
			sprintf(buffer, "SQRT");
			break;
		case ND_EXP:
			sprintf(buffer, "EXP");
			break;
		case ND_SIN:
			sprintf(buffer, "SIN");
			break;
		case ND_COS:
			sprintf(buffer, "COS");
			break;
		case ND_LOG:
			sprintf(buffer, "LOG");
			break;
		case ND_LOG10:
			sprintf(buffer, "LOG10");
			break;
		case ND_ASIN:
			sprintf(buffer, "ASIN");
			break;
		case ND_RAND:
			sprintf(buffer, "RAND");
			break;
		case ND_ROUND:
			sprintf(buffer, "ROUND");
			break;

		case ND_STRCPY:
			sprintf(buffer, "STRCPY");
			break;
		case ND_STRNCPY:
			sprintf(buffer, "STRNCPY");
			break;
		case ND_STRCAT:
			sprintf(buffer, "STRCAT");
			break;
		case ND_STRNCAT:
			sprintf(buffer, "STRNCAT");
			break;
		case ND_STRCMP:
			sprintf(buffer, "STRCMP");
			break;
		case ND_STRNCMP:
			sprintf(buffer, "STRNCMP");
			break;
		case ND_STRSTR:
			sprintf(buffer, "STRSTR");
			break;
		case ND_STRLEN:
			sprintf(buffer, "STRLENC");
			break;

		case IC_BEGINIT:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "BEGINIT");
					break;
				case 1:
					sprintf(buffer, "n");
					break;
			}
			break;
		case IC_STRUCTWITHARR:
			argc = 2;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "STRUCTWITHARR");
					break;
				case 1:
					sprintf(buffer, "displ");
					break;
				case 2:
					sprintf(buffer, "iniproc");
					break;
			}
			break;
		case IC_DEFARR:
			argc = 7;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "DEFARR");
					break;
				case 1:
					sprintf(buffer, "N");
					break;
				case 2:
					sprintf(buffer, "elem_len");
					break;
				case 3:
					sprintf(buffer, "displ");
					break;
				case 4:
					sprintf(buffer, "iniproc");
					break;
				case 5:
					sprintf(buffer, "usual");
					break;
				case 6:
					sprintf(buffer, "all");
					break;
				case 7:
					sprintf(buffer, "instruct");
					break;
			}
			break;
		case IC_ARRINIT:
			argc = 4;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "ARRINIT");
					break;
				case 1:
					sprintf(buffer, "N");
					break;
				case 2:
					sprintf(buffer, "elem_len");
					break;
				case 3:
					sprintf(buffer, "displ");
					break;
				case 4:
					sprintf(buffer, "usual");
					break;
			}
			break;
		case IC_LI:
			argc = 1;
			sprintf(buffer, "LI");
			break;
		case IC_LID:
			argc = 2;
			sprintf(buffer, "LID");
			break;
		case IC_LOAD:
			argc = 1;
			sprintf(buffer, "LOAD");
			break;
		case IC_LOADD:
			argc = 1;
			sprintf(buffer, "LOADD");
			break;
		case IC_LAT:
			sprintf(buffer, "L@");
			break;
		case IC_LATD:
			sprintf(buffer, "L@f");
			break;
		case IC_LA:
			argc = 1;
			sprintf(buffer, "LA");
			break;

		case ND_LOGOR:
		case IC_LOGOR:
			argc = 1;
			sprintf(buffer, "||");
			break;
		case ND_LOGAND:
		case IC_LOGAND:
			argc = 1;
			sprintf(buffer, "&&");
			break;
		case ND_ORASS:
		case IC_ORASS:
			argc = 1;
			sprintf(buffer, "|=");
			break;
		case ND_ORASSAT:
		case IC_ORASSAT:
			sprintf(buffer, "|=@");
			break;
		case ND_ORASSV:
		case IC_ORASSV:
			argc = 1;
			sprintf(buffer, "|=V");
			break;
		case ND_ORASSATV:
		case IC_ORASSATV:
			sprintf(buffer, "|=@V");
			break;
		case ND_OR:
		case IC_OR:
			sprintf(buffer, "|");
			break;
		case ND_EXORASS:
		case IC_EXORASS:
			argc = 1;
			sprintf(buffer, "^=");
			break;
		case ND_EXORASSAT:
		case IC_EXORASSAT:
			sprintf(buffer, "^=@");
			break;
		case ND_EXORASSV:
		case IC_EXORASSV:
			argc = 1;
			sprintf(buffer, "^=V");
			break;
		case ND_EXORASSATV:
		case IC_EXORASSATV:
			sprintf(buffer, "^=@V");
			break;
		case ND_EXOR:
		case IC_EXOR:
			sprintf(buffer, "^");
			break;
		case ND_ANDASS:
		case IC_ANDASS:
			argc = 1;
			sprintf(buffer, "&=");
			break;
		case ND_ANDASSAT:
		case IC_ANDASSAT:
			sprintf(buffer, "&=@");
			break;
		case ND_ANDASSV:
		case IC_ANDASSV:
			argc = 1;
			sprintf(buffer, "&=V");
			break;
		case ND_ANDASSATV:
		case IC_ANDASSATV:
			sprintf(buffer, "&=@V");
			break;
		case ND_AND:
		case IC_AND:
			sprintf(buffer, "&");
			break;

		case ND_EQEQ:
		case IC_EQEQ:
			sprintf(buffer, "==");
			break;
		case ND_NOTEQ:
		case IC_NOTEQ:
			sprintf(buffer, "!=");
			break;
		case ND_LT:
		case IC_LT:
			sprintf(buffer, "<");
			break;
		case ND_GT:
		case IC_GT:
			sprintf(buffer, ">");
			break;
		case ND_LE:
		case IC_LE:
			sprintf(buffer, "<=");
			break;
		case ND_GE:
		case IC_GE:
			sprintf(buffer, ">=");
			break;
		case ND_EQEQR:
		case IC_EQEQR:
			sprintf(buffer, "==f");
			break;
		case ND_NOTEQR:
		case IC_NOTEQR:
			sprintf(buffer, "!=f");
			break;
		case ND_LTR:
		case IC_LTR:
			sprintf(buffer, "<f");
			break;
		case ND_GTR:
		case IC_GTR:
			sprintf(buffer, ">f");
			break;
		case ND_LER:
		case IC_LER:
			sprintf(buffer, "<=f");
			break;
		case ND_GER:
		case IC_GER:
			sprintf(buffer, ">=f");
			break;

		case ND_SHRASS:
		case IC_SHRASS:
			argc = 1;
			sprintf(buffer, ">>=");
			break;
		case ND_SHRASSAT:
		case IC_SHRASSAT:
			sprintf(buffer, ">>=@");
			break;
		case ND_SHRASSV:
		case IC_SHRASSV:
			argc = 1;
			sprintf(buffer, ">>=V");
			break;
		case ND_SHRASSATV:
		case IC_SHRASSATV:
			sprintf(buffer, ">>=@V");
			break;
		case ND_SHR:
		case IC_SHR:
			sprintf(buffer, ">>");
			break;
		case ND_SHLASS:
		case IC_SHLASS:
			argc = 1;
			sprintf(buffer, "<<=");
			break;
		case ND_SHLASSAT:
		case IC_SHLASSAT:
			sprintf(buffer, "<<=@");
			break;
		case ND_SHLASSV:
		case IC_SHLASSV:
			argc = 1;
			sprintf(buffer, "<<=V");
			break;
		case ND_SHLASSATV:
		case IC_SHLASSATV:
			sprintf(buffer, "<<=@V");
			break;
		case ND_SHL:
		case IC_SHL:
			sprintf(buffer, "<<");
			break;

		case ND_ASS:
		case IC_ASS:
			argc = 1;
			sprintf(buffer, "=");
			break;
		case ND_ASSAT:
		case IC_ASSAT:
			sprintf(buffer, "=@");
			break;
		case ND_ASSV:
		case IC_ASSV:
			argc = 1;
			sprintf(buffer, "=V");
			break;
		case ND_ASSATV:
		case IC_ASSATV:
			sprintf(buffer, "=@V");
			break;

		case ND_PLUSASS:
		case IC_PLUSASS:
			argc = 1;
			sprintf(buffer, "+=");
			break;
		case ND_PLUSASSAT:
		case IC_PLUSASSAT:
			sprintf(buffer, "+=@");
			break;
		case ND_PLUSASSV:
		case IC_PLUSASSV:
			argc = 1;
			sprintf(buffer, "+=V");
			break;
		case ND_PLUSASSATV:
		case IC_PLUSASSATV:
			sprintf(buffer, "+=@V");
			break;
		case ND_PLUS:
		case IC_PLUS:
			sprintf(buffer, "+");
			break;

		case ND_MINUSASS:
		case IC_MINUSASS:
			argc = 1;
			sprintf(buffer, "-=");
			break;
		case ND_MINUSASSAT:
		case IC_MINUSASSAT:
			sprintf(buffer, "-=@");
			break;
		case ND_MINUSASSV:
		case IC_MINUSASSV:
			argc = 1;
			sprintf(buffer, "-=V");
			break;
		case ND_MINUSASSATV:
		case IC_MINUSASSATV:
			sprintf(buffer, "-=@V");
			break;
		case ND_MINUS:
		case IC_MINUS:
			sprintf(buffer, "-");
			break;

		case ND_MULTASS:
		case IC_MULTASS:
			argc = 1;
			sprintf(buffer, "*=");
			break;
		case ND_MULTASSAT:
		case IC_MULTASSAT:
			sprintf(buffer, "*=@");
			break;
		case ND_MULTASSV:
		case IC_MULTASSV:
			argc = 1;
			sprintf(buffer, "*=V");
			break;
		case ND_MULTASSATV:
		case IC_MULTASSATV:
			sprintf(buffer, "*=@V");
			break;
		case ND_MULT:
		case IC_MULT:
			sprintf(buffer, "*");
			break;

		case ND_DIVASS:
		case IC_DIVASS:
			argc = 1;
			sprintf(buffer, "/=");
			break;
		case ND_DIVASSAT:
		case IC_DIVASSAT:
			sprintf(buffer, "/=@");
			break;
		case ND_DIVASSV:
		case IC_DIVASSV:
			argc = 1;
			sprintf(buffer, "/=V");
			break;
		case ND_DIVASSATV:
		case IC_DIVASSATV:
			sprintf(buffer, "/=@V");
			break;
		case ND_DIV:
		case IC_DIV:
			sprintf(buffer, "/");
			break;

		case ND_ASSR:
		case IC_ASSR:
			argc = 1;
			sprintf(buffer, "=f");
			break;
		case ND_ASSRV:
		case IC_ASSRV:
			argc = 1;
			sprintf(buffer, "=fV");
			break;
		case ND_ASSATR:
		case IC_ASSATR:
			sprintf(buffer, "=@f");
			break;
		case ND_ASSATRV:
		case IC_ASSATRV:
			sprintf(buffer, "=@fV");
			break;

		case ND_PLUSASSR:
		case IC_PLUSASSR:
			argc = 1;
			sprintf(buffer, "+=f");
			break;
		case ND_PLUSASSATR:
		case IC_PLUSASSATR:
			sprintf(buffer, "+=@f");
			break;
		case ND_PLUSASSRV:
		case IC_PLUSASSRV:
			argc = 1;
			sprintf(buffer, "+=fV");
			break;
		case ND_PLUSASSATRV:
		case IC_PLUSASSATRV:
			sprintf(buffer, "+=@fV");
			break;
		case ND_PLUSR:
		case IC_PLUSR:
			sprintf(buffer, "+f");
			break;
		case ND_MINUSASSR:
		case IC_MINUSASSR:
			argc = 1;
			sprintf(buffer, "-=f");
			break;
		case ND_MINUSASSATR:
		case IC_MINUSASSATR:
			sprintf(buffer, "-=@f");
			break;
		case ND_MINUSASSRV:
		case IC_MINUSASSRV:
			argc = 1;
			sprintf(buffer, "-=fV");
			break;
		case ND_MINUSASSATRV:
		case IC_MINUSASSATRV:
			sprintf(buffer, "-=@fV");
			break;
		case ND_MINUSR:
		case IC_MINUSR:
			sprintf(buffer, "-f");
			break;
		case ND_MULTASSR:
		case IC_MULTASSR:
			argc = 1;
			sprintf(buffer, "*=f");
			break;
		case ND_MULTASSATR:
		case IC_MULTASSATR:
			sprintf(buffer, "*=@f");
			break;
		case ND_MULTASSRV:
		case IC_MULTASSRV:
			argc = 1;
			sprintf(buffer, "*=fV");
			break;
		case ND_MULTASSATRV:
		case IC_MULTASSATRV:
			sprintf(buffer, "*=@fV");
			break;
		case ND_MULTR:
		case IC_MULTR:
			sprintf(buffer, "*f");
			break;
		case ND_DIVASSR:
		case IC_DIVASSR:
			argc = 1;
			sprintf(buffer, "/=f");
			break;
		case ND_DIVASSATR:
		case IC_DIVASSATR:
			sprintf(buffer, "/=@f");
			break;
		case ND_DIVASSRV:
		case IC_DIVASSRV:
			argc = 1;
			sprintf(buffer, "/=fV");
			break;
		case ND_DIVASSATRV:
		case IC_DIVASSATRV:
			sprintf(buffer, "/=@fV");
			break;
		case ND_DIVR:
		case IC_DIVR:
			sprintf(buffer, "/f");
			break;

		case ND_REMASS:
		case IC_REMASS:
			argc = 1;
			sprintf(buffer, "%%=");
			break;
		case ND_REMASSAT:
		case IC_REMASSAT:
			sprintf(buffer, "%%=@");
			break;
		case ND_REMASSV:
		case IC_REMASSV:
			argc = 1;
			sprintf(buffer, "%%=V");
			break;
		case ND_REMASSATV:
		case IC_REMASSATV:
			sprintf(buffer, "%%=@V");
			break;
		case ND_REM:
		case IC_REM:
			sprintf(buffer, "%%");
			break;

		case IC_CALL1:
			sprintf(buffer, "CALL1");
			break;
		case IC_CALL2:
			argc = 1;
			sprintf(buffer, "CALL2");
			break;
		case IC_STOP:
			sprintf(buffer, "STOP");
			break;
		case IC_RETURNVAL:
			argc = 1;
			sprintf(buffer, "RETURNVAL");
			break;
		case IC_RETURNVOID:
			sprintf(buffer, "RETURNVOID");
			break;
		case IC_B:
			argc = 1;
			sprintf(buffer, "B");
			break;
		case IC_BE0:
			argc = 1;
			sprintf(buffer, "BE0");
			break;
		case IC_BNE0:
			argc = 1;
			sprintf(buffer, "BNE0");
			break;
		case IC_SLICE:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "SLICE");
					break;
				case 1:
					sprintf(buffer, "d");
					break;
			}
			break;
		case IC_SELECT:
			argc = 1;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "SELECT");
					break;
				case 1:
					sprintf(buffer, "field_displ");
					break;
			}
			break;
		case ND_WIDEN:
		case IC_WIDEN:
			sprintf(buffer, "WIDEN");
			break;
		case ND_WIDEN1:
		case IC_WIDEN1:
			sprintf(buffer, "WIDEN1");
			break;
		case IC__DOUBLE:
			sprintf(buffer, "DOUBLE");
			break;
		case ND_INC:
		case IC_INC:
			argc = 1;
			sprintf(buffer, "INC");
			break;
		case ND_DEC:
		case IC_DEC:
			argc = 1;
			sprintf(buffer, "DEC");
			break;
		case ND_POSTINC:
		case IC_POSTINC:
			argc = 1;
			sprintf(buffer, "POSTINC");
			break;
		case ND_POSTDEC:
		case IC_POSTDEC:
			argc = 1;
			sprintf(buffer, "POSTDEC");
			break;
		case ND_INCAT:
		case IC_INCAT:
			sprintf(buffer, "INC@");
			break;
		case ND_DECAT:
		case IC_DECAT:
			sprintf(buffer, "DEC@");
			break;
		case ND_POSTINCAT:
		case IC_POSTINCAT:
			sprintf(buffer, "POSTINC@");
			break;
		case ND_POSTDECAT:
		case IC_POSTDECAT:
			sprintf(buffer, "POSTDEC@");
			break;
		case ND_INCR:
		case IC_INCR:
			argc = 1;
			sprintf(buffer, "INCf");
			break;
		case ND_DECR:
		case IC_DECR:
			argc = 1;
			sprintf(buffer, "DECf");
			break;
		case ND_POSTINCR:
		case IC_POSTINCR:
			argc = 1;
			sprintf(buffer, "POSTINCf");
			break;
		case ND_POSTDECR:
		case IC_POSTDECR:
			argc = 1;
			sprintf(buffer, "POSTDECf");
			break;
		case ND_INCATR:
		case IC_INCATR:
			sprintf(buffer, "INC@f");
			break;
		case ND_DECATR:
		case IC_DECATR:
			sprintf(buffer, "DEC@f");
			break;
		case ND_POSTINCATR:
		case IC_POSTINCATR:
			sprintf(buffer, "POSTINC@f");
			break;
		case ND_POSTDECATR:
		case IC_POSTDECATR:
			sprintf(buffer, "POSTDEC@f");
			break;
		case ND_INCV:
		case IC_INCV:
			argc = 1;
			sprintf(buffer, "INCV");
			break;
		case ND_DECV:
		case IC_DECV:
			argc = 1;
			sprintf(buffer, "DECV");
			break;
		case ND_POSTINCV:
		case IC_POSTINCV:
			argc = 1;
			sprintf(buffer, "POSTINCV");
			break;
		case ND_POSTDECV:
		case IC_POSTDECV:
			argc = 1;
			sprintf(buffer, "POSTDECV");
			break;
		case ND_INCATV:
		case IC_INCATV:
			sprintf(buffer, "INC@V");
			break;
		case ND_DECATV:
		case IC_DECATV:
			sprintf(buffer, "DEC@V");
			break;
		case ND_POSTINCATV:
		case IC_POSTINCATV:
			sprintf(buffer, "POSTINC@V");
			break;
		case ND_POSTDECATV:
		case IC_POSTDECATV:
			sprintf(buffer, "POSTDEC@V");
			break;
		case ND_INCRV:
		case IC_INCRV:
			argc = 1;
			sprintf(buffer, "INCfV");
			break;
		case ND_DECRV:
		case IC_DECRV:
			argc = 1;
			sprintf(buffer, "DECfV");
			break;
		case ND_POSTINCRV:
		case IC_POSTINCRV:
			argc = 1;
			sprintf(buffer, "POSTINCfV");
			break;
		case ND_POSTDECRV:
		case IC_POSTDECRV:
			argc = 1;
			sprintf(buffer, "POSTDECfV");
			break;
		case ND_INCATRV:
		case IC_INCATRV:
			sprintf(buffer, "INC@fV");
			break;
		case ND_DECATRV:
		case IC_DECATRV:
			sprintf(buffer, "DEC@fV");
			break;
		case ND_POSTINCATRV:
		case IC_POSTINCATRV:
			sprintf(buffer, "POSTINC@fV");
			break;
		case ND_POSTDECATRV:
		case IC_POSTDECATRV:
			sprintf(buffer, "POSTDEC@fV");
			break;

		case ND_NOT:
		case IC_NOT:
			sprintf(buffer, "BITNOT");
			break;
		case ND_LOGNOT:
		case IC_LOGNOT:
			sprintf(buffer, "NOT");
			break;
		case ND_UNMINUS:
		case IC_UNMINUS:
			sprintf(buffer, "UNMINUS");
			break;
		case ND_UNMINUSR:
		case IC_UNMINUSR:
			sprintf(buffer, "UNMINUSf");
			break;

		case IC_FUNCBEG:
			argc = 2;
			was_switch = 1;
			switch (num)
			{
				case 0:
					sprintf(buffer, "FUNCBEG");
					break;
				case 1:
					sprintf(buffer, "maxdispl");
					break;
				case 2:
					sprintf(buffer, "pc");
					break;
			}
			break;

		default:
			sprintf(buffer, "%" PRIitem, elem);
			break;
	}

	if ((num != 0 && !was_switch) || argc < num)
	{
		buffer[0] = '\0';
	}
	return argc;
}


void double_to_io(universal_io *const io, const int64_t fst, const int64_t snd)
{
	int64_t num = (snd << 32) | (fst & 0x00000000ffffffff);
	double numdouble;
	memcpy(&numdouble, &num, sizeof(double));
	uni_printf(io, " %f\n", numdouble);
}

size_t elem_to_io(universal_io *const io, const vector *const table, size_t i)
{
	const item_t type = vector_get(table, i++);

	char buffer[MAX_ELEM_SIZE];
	size_t argc = elem_get_name(type, 0, buffer);
	uni_printf(io, "%s", buffer);

	if (type == ND_CONST || type == IC_LID)
	{
		double_to_io(io, vector_get(table, i), vector_get(table, i + 1));
		return i + 2;
	}

	for (size_t j = 1; j <= argc; j++)
	{
		elem_get_name(type, j, buffer);

		if (buffer[0] != '\0')
		{
			uni_printf(io, " %s=", buffer);
		}

		uni_printf(io, " %" PRIitem, vector_get(table, i++));
	}
	uni_printf(io, "\n");

	if (type == ND_STRING)
	{
		const size_t n = (size_t)vector_get(table, i - 1);
		for (size_t j = 0; j < n; j++)
		{
			uni_printf(io, "%" PRIitem "\n", vector_get(table, i++));
		}
	}
	else if (type == ND_STRINGD)
	{
		const size_t n = (size_t)vector_get(table, i - 1);
		for (size_t j = 0; j < n; j++)
		{
			double_to_io(io, vector_get(table, i), vector_get(table, i + 1));
			i += 2;
		}
	}

	return i;
}


size_t tree_print_recursive(universal_io *const io, node *const nd, size_t index, size_t tabs)
{
	for (size_t i = 0; i < tabs; i++)
	{
		uni_printf(io, INDENT);
	}
	uni_printf(io, "tc %zi) ", index);

	const item_t type = node_get_type(nd);
	char buffer[MAX_ELEM_SIZE];
	size_t argc = elem_get_name(type, 0, buffer);
	uni_printf(io, "%s", buffer);

	if (type == ND_CONSTD || type == IC_LID)
	{
		double_to_io(io, node_get_arg(nd, 0), node_get_arg(nd, 1));
	}
	else
	{
		size_t i = 0;
		while (i < argc && node_get_arg(nd, i) != ITEM_MAX)
		{
			elem_get_name(type, i + 1, buffer);

			if (buffer[0] != '\0')
			{
				uni_printf(io, " %s=", buffer);
			}

			uni_printf(io, " %" PRIitem, node_get_arg(nd, i++));
		}
		uni_printf(io, "\n");

		if ((node_get_arg(nd, i) != ITEM_MAX && node_get_type(nd) != ND_STRING && node_get_type(nd) != ND_STRINGD)
			|| i != argc)
		{
			elem_get_name(type, 0, buffer);
			warning(NULL, node_argc, index, buffer);
		}
	}

	index += argc + 1;
	for (size_t j = 0; j < node_get_amount(nd); j++)
	{
		node child = node_get_child(nd, j);
		index = tree_print_recursive(io, &child, index, tabs + 1);
	}

	return index;
}


/*
 *	 __     __   __     ______   ______     ______     ______   ______     ______     ______
 *	/\ \   /\ "-.\ \   /\__  _\ /\  ___\   /\  == \   /\  ___\ /\  __ \   /\  ___\   /\  ___\
 *	\ \ \  \ \ \-.  \  \/_/\ \/ \ \  __\   \ \  __<   \ \  __\ \ \  __ \  \ \ \____  \ \  __\
 *	 \ \_\  \ \_\\"\_\    \ \_\  \ \_____\  \ \_\ \_\  \ \_\    \ \_\ \_\  \ \_____\  \ \_____\
 *	  \/_/   \/_/ \/_/     \/_/   \/_____/   \/_/ /_/   \/_/     \/_/\/_/   \/_____/   \/_____/
 */


/** Вывод таблиц и дерева */
void tables_and_tree(const char *const path
	, const vector *const identifiers
	, const vector *const modes
	, vector *const tree)
{
	universal_io io = io_create();
	if (!vector_is_correct(identifiers) || !vector_is_correct(modes) || !vector_is_correct(tree)
		|| out_set_file(&io, path))
	{
		return;
	}


	uni_printf(&io, "identab\n");
	for (size_t i = 2; i < vector_size(identifiers); i += 4)
	{
		for (size_t j = 0; j < 4; j++)
		{
			uni_printf(&io, "id %zi) %" PRIitem "\n", i + j, vector_get(identifiers, i + j));
		}
		uni_printf(&io, "\n");
	}

	uni_printf(&io, "\nmodetab\n");
	for (size_t i = 0; i < vector_size(modes); i++)
	{
		uni_printf(&io, "md %zi) %" PRIitem "\n", i, vector_get(modes, i));
	}

	uni_printf(&io, "\n\ntree\n");
	size_t i = 0;
#ifdef OLD_TREE
	while (i < vector_size(tree))
	{
		uni_printf(&io, "tc %zi) ", i);
		i = elem_to_io(&io, tree, i);
	}
#else
	node nd = node_get_root(tree);
	for (size_t j = 0; j < node_get_amount(&nd); j++)
	{
		node child = node_get_child(&nd, j);
		i = tree_print_recursive(&io, &child, i, 0);
	}
#endif

	io_erase(&io);
}

/** Вывод таблиц и кодов */
void tables_and_codes(const char *const path
	, const vector *const functions
	, const vector *const processes
	, const vector *const memory)
{
	universal_io io = io_create();
	if (!vector_is_correct(functions) || !vector_is_correct(processes) || !vector_is_correct(memory)
		|| out_set_file(&io, path))
	{
		return;
	}


	uni_printf(&io, "functions\n");
	for (size_t i = 0; i < vector_size(functions); i++)
	{
		uni_printf(&io, "fun %zi) %" PRIitem "\n", i, vector_get(functions, i));
	}

	uni_printf(&io, "\n\niniprocs\n");
	for (size_t i = 0; i < vector_size(processes); i++)
	{
		uni_printf(&io, "inipr %zi) %" PRIitem "\n", i, vector_get(processes, i));
	}

	uni_printf(&io, "\n\nmem\n");
	size_t i = 0;
	while (i < vector_size(memory))
	{
		uni_printf(&io, "pc %zi) ", i);
		i = elem_to_io(&io, memory, i);
	}

	io_erase(&io);
}
