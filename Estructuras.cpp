#include "Estructuras.h"



Arbol::Arbol(ECampos pType, tipo_Arbol pTipo_Arbol)
{
	aRoot = NULL;
	aType = pType;
	aTipo_Arbol = pTipo_Arbol;
}

Arbol::~Arbol(void)
{
	clean();
}

void Arbol::cleanr(PTNODE pSub)
{
	if (aRoot)
	{
		PTNODE lTemp = aRoot;
		if (pSub)
		{
			lTemp = pSub;
		}

		if (lTemp->sLft)
		{
			cleanr(lTemp->sLft);
		}
		if (lTemp->sRgt)
		{
			cleanr(lTemp->sRgt);
		}
		bool lRoot = lTemp == aRoot;
		delete lTemp;

		if (lRoot)
		{
			aRoot = NULL;
		}

	}

}



void Arbol::clean()
{
	if (aRoot)
	{
		PTNODE lTemp = aRoot;
		PTNODE lTemp_borrado = NULL;
		stack <PTNODE> lStack; //Pila
		if (lTemp)
		{
			lStack.push(lTemp);
			lTemp = lTemp->sLft;
		}
		else
		{
			lTemp = lStack.top();
			lStack.pop();
			lTemp_borrado = lTemp;
			lTemp = lTemp->sRgt;
			delete lTemp_borrado;
		}
	}
}


int Arbol::comp(PDATA pA, PDATA pB)
{
	int lRes = 0;

	switch (aType) {
	case ECampos::nombre:
		if (pA->sNombre < pB->sNombre) lRes = -1;
		else if (pA->sNombre == pB->sNombre) lRes = 0;
		else lRes = 1;
		break;
	case ECampos::apellido:
		if (pA->sApellido < pB->sApellido) lRes = -1;
		else if (pA->sApellido == pB->sApellido) lRes = 0;
		else lRes = 1;
		break;
	case ECampos::fnac:
		if (pA->sFNac < pB->sFNac) lRes = -1;
		else if (pA->sFNac == pB->sFNac) lRes = 0;
		else lRes = 1;
		break;
	case ECampos::salario:
		if (pA->sSalario < pB->sSalario) lRes = -1;
		else if (pA->sSalario == pB->sSalario) lRes = 0;
		else lRes = 1;
		break;
	}

	return lRes;
} // comp




void Arbol::pushr(PDATA pData, PTNODE pSub)
{

	if (aRoot == NULL)
	{
		aRoot = getNewNode(pData);
	}
	else
	{
		PTNODE lTemp = aRoot;
		switch (aTipo_Arbol)
		{
		case (tipo_Arbol::Normal):
		{
			if (pSub)
			{
				lTemp = pSub;
			}
			if (comp(pData,lTemp->sData) == -1)
			{
				if (lTemp->sLft)
				{
					pushr(pData, lTemp->sLft);
				}
				else
				{
					lTemp->sLft = getNewNode(pData);
				}
			}
			else if (comp(pData, lTemp->sData) >= 0)
			{
				if (lTemp->sRgt)
				{
					pushr(pData, lTemp->sRgt);
				}
				else
				{
					lTemp->sRgt = getNewNode(pData);
				}
			}
			break;
		}
		case (tipo_Arbol::NoRepeticiones):
		{
			if (pSub)
			{
				lTemp = pSub;
			}
			if (comp(pData, lTemp->sData) == -1)
			{
				if (lTemp->sLft)
				{
					pushr(pData, lTemp->sLft);
				}
				else
				{
					lTemp->sLft = getNewNode(pData);
				}
			}
			else if (comp(pData, lTemp->sData) == 1)
			{
				if (lTemp->sRgt)
				{
					pushr(pData, lTemp->sRgt);
				}
				else
				{
					lTemp->sRgt = getNewNode(pData);
				}
			}
			break;
		}
		case (tipo_Arbol::Frecuencia):
		{
			if (pSub)
			{
				lTemp = pSub;
			}
			if (comp(pData, lTemp->sData) == -1)
			{
				if (lTemp->sLft)
				{
					pushr(pData, lTemp->sLft);
				}
				else
				{
					lTemp->sLft = getNewNode(pData);
				}
			}
			else if (comp(pData, lTemp->sData) == 1)
			{
				if (lTemp->sRgt)
				{
					pushr(pData, lTemp->sRgt);
				}
				else
				{
					lTemp->sRgt = getNewNode(pData);
				}
			}
			else
			{
				lTemp->sFrec++;
			}

			break;
		}
		default:
		{
			break;
		}
		}
	}

}


void Arbol::push(PDATA pData)
{
	if (aRoot == NULL)
	{
		aRoot = getNewNode(pData);
	}
	else
	{
		PTNODE lTemp = aRoot;
		switch (aTipo_Arbol)
		{
		case tipo_Arbol::Normal:
		{
			while (lTemp)
			{
				if (comp(pData, lTemp->sData) == -1)
				{ //Menores
					if (lTemp->sLft)
					{
						lTemp = lTemp->sLft;
					}
					else
					{
						lTemp->sLft = getNewNode(pData);
						lTemp = NULL;
					}
				}

				else if (comp(pData, lTemp->sData) ==  1)
				{//Mayores
					if (lTemp->sRgt)
					{
						lTemp = lTemp->sRgt;
					}
					else
					{
						lTemp->sRgt = getNewNode(pData);
						lTemp = NULL;
					}
				}
				else
				{//Iguales. Hay que modificar
					if (lTemp->sRgt)
					{
						lTemp = lTemp->sRgt;
					}
					else
					{
						lTemp->sRgt = getNewNode(pData);
						lTemp = NULL;
					}
				}
			}
			break;
		}

		case tipo_Arbol::NoRepeticiones:
		{
			while (lTemp)
			{
				if (comp(pData, lTemp->sData) == -1)
				{ //Menores
					if (lTemp->sLft)
					{
						lTemp = lTemp->sLft;
					}
					else
					{
						lTemp->sLft = getNewNode(pData);
						lTemp = NULL;
					}
				}

				else if (comp(pData, lTemp->sData) == 1)
				{//Mayores
					if (lTemp->sRgt)
					{
						lTemp = lTemp->sRgt;
					}
					else
					{
						lTemp->sRgt = getNewNode(pData);
						lTemp = NULL;
					}
				}
				else
				{//Iguales. Hay que modificar
					lTemp = NULL;
				}
			}
			break;
		}


		case tipo_Arbol::Frecuencia:
		{
			while (lTemp)
			{
				if (comp(pData, lTemp->sData) == -1)
				{ //Menores
					if (lTemp->sLft)
					{
						lTemp = lTemp->sLft;
					}
					else
					{
						lTemp->sLft = getNewNode(pData);
						lTemp = NULL;
					}
				}

				else if (comp(pData, lTemp->sData) == 1)
				{//Mayores
					if (lTemp->sRgt)
					{
						lTemp = lTemp->sRgt;
					}
					else
					{
						lTemp->sRgt = getNewNode(pData);
						lTemp = NULL;
					}
				}
				else
				{//Iguales. Hay que modificar
					lTemp->sFrec++;
					lTemp = NULL;
				}
			}
			break;
		}

		}
	}
}




void Arbol::reprr(Orden pOrd, PTNODE pSub)
{
	if (aRoot)
	{
		PTNODE lTemp = aRoot;
		if (pSub)
		{
			lTemp = pSub;
		}
		switch (pOrd)
		{
		case Orden::asc:
		{
			if (lTemp->sLft)
			{
				reprr(pOrd, lTemp->sLft);
			}
			cout << "( " << lTemp->sData->sNombre << ", " << lTemp->sData->sApellido << ", " << lTemp->sData->sFNac << ", " << lTemp->sData->sSalario << ") , ";
			if (lTemp->sRgt)
			{
				reprr(pOrd, lTemp->sRgt);
			}
			break;
		}
		case Orden::desc:
		{
			if (lTemp->sRgt)
			{
				reprr(pOrd, lTemp->sRgt);
			}
			cout << "( " << lTemp->sData->sNombre << ", " << lTemp->sData->sApellido << ", " << lTemp->sData->sFNac << ", " << lTemp->sData->sSalario << ") , ";
			if (lTemp->sLft)
			{
				reprr(pOrd, lTemp->sLft);
			}
			break;
		}

		case Orden::sinorden:
		{
			cout << "( " << lTemp->sData->sNombre << ", " << lTemp->sData->sApellido << ", " << lTemp->sData->sFNac << ", " << lTemp->sData->sSalario << ") , ";
			if (lTemp->sLft)
			{
				reprr(pOrd, lTemp->sLft);
			}
			if (lTemp->sRgt)
			{
				reprr(pOrd, lTemp->sRgt);
			}

		}

		}



	}
}


void Arbol::repr(Orden pOrd)
{
	if (aRoot)
	{
		PTNODE lTemp = aRoot;
		stack <PTNODE> lStack; //Pila

		switch (aTipo_Arbol)
		{
		case tipo_Arbol::Frecuencia:
		{
			while (lTemp || (lStack.empty() == false))
			{
				switch (pOrd)
				{
				case Orden::asc:
				{
					if (lTemp)
					{
						lStack.push(lTemp);
						lTemp = lTemp->sLft;
					}
					else
					{
						lTemp = lStack.top();
						lStack.pop();
						cout << "( " << lTemp->sData->sNombre << ", " << lTemp->sData->sApellido << ", " << lTemp->sData->sFNac << ", " << lTemp->sData->sSalario << ") [" << lTemp->sFrec << "] ) ,";  //En lugar de un cout hacer un delete y antes verificar si el lTemp igual al aRoot
						lTemp = lTemp->sRgt;
					}
					break;
				}
				case Orden::desc:
				{
					if (lTemp)
					{
						lStack.push(lTemp);
						lTemp = lTemp->sRgt;
					}
					else
					{
						lTemp = lStack.top();
						lStack.pop();
						cout << "( " << lTemp->sData->sNombre << ", " << lTemp->sData->sApellido << ", " << lTemp->sData->sFNac << ", " << lTemp->sData->sSalario << ") [" << lTemp->sFrec << "] ) ,";
						lTemp = lTemp->sLft;
					}
					break;
				}
				case Orden::sinorden:
				{
					if (lTemp)
					{
						cout << "( " << lTemp->sData->sNombre << ", " << lTemp->sData->sApellido << ", " << lTemp->sData->sFNac << ", " << lTemp->sData->sSalario << ") [" << lTemp->sFrec << "] ) ,";
						lStack.push(lTemp);
						lTemp = lTemp->sLft;
					}
					else
					{
						lTemp = lStack.top();
						lStack.pop();
						lTemp = lTemp->sRgt;
					}
					break;
				}
				}
			}
			break;
		}

		default:
		{
			while (lTemp || (lStack.empty() == false))
			{
				switch (pOrd)
				{
				case Orden::asc:
				{
					if (lTemp)
					{
						lStack.push(lTemp);
						lTemp = lTemp->sLft;
					}
					else
					{
						lTemp = lStack.top();
						lStack.pop();
						cout << "( " << lTemp->sData->sNombre << ", " << lTemp->sData->sApellido << ", " << lTemp->sData->sFNac << ", " << lTemp->sData->sSalario << ") , ";  //En lugar de un cout hacer un delete y antes verificar si el lTemp igual al aRoot
						lTemp = lTemp->sRgt;
					}
					break;
				}
				case Orden::desc:
				{
					if (lTemp)
					{
						lStack.push(lTemp);
						lTemp = lTemp->sRgt;
					}
					else
					{
						lTemp = lStack.top();
						lStack.pop();
						cout << "( " << lTemp->sData->sNombre << ", " << lTemp->sData->sApellido << ", " << lTemp->sData->sFNac << ", " << lTemp->sData->sSalario << ") , ";
						lTemp = lTemp->sLft;
					}
					break;
				}
				case Orden::sinorden:
				{
					if (lTemp)
					{
						cout << "( " << lTemp->sData->sNombre << ", " << lTemp->sData->sApellido << ", " << lTemp->sData->sFNac << ", " << lTemp->sData->sSalario << ") , ";
						lStack.push(lTemp);
						lTemp = lTemp->sLft;
					}
					else
					{
						lTemp = lStack.top();
						lStack.pop();
						lTemp = lTemp->sRgt;
					}
					break;
				}
				}
			}
			break;
		}

		}

	}
}

void Arbol::delr(PDATA pData)
{
	if (aRoot)
	{
		pdelr(aRoot, pData);
	}
}

/*
void Arbol::runGet(void(*pFunc)(string))
{
	if (aRoot && (pFunc != NULL))
	{
		PTNODE lTemp = aRoot;
		stack <PTNODE> lStack; //Pila
		while (lTemp || (lStack.empty() == false))
		{

			if (lTemp)
			{
				lStack.push(lTemp);
				lTemp = lTemp->sLft;
			}
			else
			{
				lTemp = lStack.top();
				lStack.pop();
				pFunc(lTemp->sVal + to_string(lTemp->sFrec));
				lTemp = lTemp->sRgt;
			}
		}
	}
}
*/


PTNODE Arbol::pdelr(PTNODE pSub, PDATA pData)
{
	switch (aTipo_Arbol)
	{
	case tipo_Arbol::Frecuencia:
	{
		if (pSub == NULL)
		{
			return pSub;
		}

		if (comp(pData,pSub->sData) == -1)
		{
			//Menores
			pSub->sLft = pdelr(pSub->sLft, pData);
		}
		else if (comp(pData, pSub->sData) == 1)
		{
			//Mayores
			pSub->sRgt = pdelr(pSub->sRgt, pData);
		}
		else
		{
			//Igual
			pSub->sFrec--;

			if (pSub->sFrec == 0)
			{
				//0 o +1 hijos
				if (pSub->sLft == NULL)
				{
					PTNODE lTemp = pSub->sRgt;
					delete pSub;
					return lTemp;
				}
				else if (pSub->sRgt == NULL)
				{
					PTNODE lTemp = pSub->sLft;
					delete pSub;
					return lTemp;
				}

				// 2 hijos
				PTNODE lTemp = min(pSub->sRgt);

				pSub->sData = lTemp->sData; //Borrado Virtual

				pSub->sRgt = pdelr(pSub->sRgt, lTemp->sData);
			}

		}
		return pSub;
		break;
	}

	default:
	{
		if (pSub == NULL)
		{
			return pSub;
		}

		if (comp(pData, pSub->sData) == -1)
		{
			//Menores
			pSub->sLft = pdelr(pSub->sLft, pData);
		}
		else if (comp(pData, pSub->sData) == 1)
		{
			//Mayores
			pSub->sRgt = pdelr(pSub->sRgt, pData);
		}
		else
		{
			//Igual

			//0 o +1 hijos
			if (pSub->sLft == NULL)
			{
				PTNODE lTemp = pSub->sRgt;
				delete pSub;
				return lTemp;
			}
			else if (pSub->sRgt == NULL)
			{
				PTNODE lTemp = pSub->sLft;
				delete pSub;
				return lTemp;
			}

			// 2 hijos
			PTNODE lTemp = min(pSub->sRgt);

			pSub->sData = lTemp->sData; //Borrado Virtual

			pSub->sRgt = pdelr(pSub->sRgt, lTemp->sData);

		}
		return pSub;



		break;

	}
	}

}

PTNODE Arbol::min(PTNODE pSub)
{
	PTNODE lTemp = pSub;
	while (lTemp && (lTemp->sLft))
	{
		lTemp = lTemp->sLft;
	}

	return lTemp;
}


/*
void Arbol::read(string pPath)
{
	auto lStart = chrono::high_resolution_clock::now();
	string lLine = "";
	ifstream lFile(pPath);

	while (getline(lFile, lLine)) {
		//lLine = lLine.substr(lLine.find_first_not_of(" "), lLine.find_last_not_of(" ") + 1);
		push(lLine);
	}

	lFile.close();

	auto lElapsed = chrono::high_resolution_clock::now() - lStart;
	long long lMS = chrono::duration_cast<chrono::microseconds>
		(lElapsed).count();
	cout << lMS << " microsseconds" << endl;
}
*/


void Arbol::write(string pPath, Orden pOrd)
{
	if (aRoot)
	{
		PTNODE lTemp = aRoot;
		stack <PTNODE> lStack; //Pila
		ofstream lFile(pPath);
		if (lFile.is_open())
		{
			switch (aTipo_Arbol)
			{
			case tipo_Arbol::Frecuencia:
			{
				while (lTemp || (lStack.empty() == false))
				{
					switch (pOrd)
					{
					case Orden::asc:
					{
						if (lTemp)
						{
							lStack.push(lTemp);
							lTemp = lTemp->sLft;
						}
						else
						{
							lTemp = lStack.top();
							lStack.pop();
							for (int i = 0; i < lTemp->sFrec; i++)
							{
								lFile << lTemp->sData->sNombre << " " << lTemp->sData->sApellido << " " << lTemp->sData->sFNac << " " << lTemp->sData->sSalario << endl;  //En lugar de un cout hacer un delete y antes verificar si el lTemp igual al aRoot
							}
							lTemp = lTemp->sRgt;
						}
						break;
					}
					case Orden::desc:
					{
						if (lTemp)
						{
							lStack.push(lTemp);
							lTemp = lTemp->sRgt;
						}
						else
						{
							lTemp = lStack.top();
							lStack.pop();
							for (int i = 0; i < lTemp->sFrec; i++)
							{
								lFile << lTemp->sData->sNombre << " " << lTemp->sData->sApellido << " " << lTemp->sData->sFNac << " " << lTemp->sData->sSalario << endl;
							}
							lTemp = lTemp->sLft;
						}
						break;
					}
					case Orden::sinorden:
					{
						if (lTemp)
						{
							for (int i = 0; i < lTemp->sFrec; i++)
							{
								lFile << lTemp->sData->sNombre << " " << lTemp->sData->sApellido << " " << lTemp->sData->sFNac << " " << lTemp->sData->sSalario << endl;
							}
							lStack.push(lTemp);
							lTemp = lTemp->sLft;
						}
						else
						{
							lTemp = lStack.top();
							lStack.pop();
							lTemp = lTemp->sRgt;
						}
						break;
					}
					}
				}
				break;
			}

			default:
			{
				while (lTemp || (lStack.empty() == false))
				{
					switch (pOrd)
					{
					case Orden::asc:
					{
						if (lTemp)
						{
							lStack.push(lTemp);
							lTemp = lTemp->sLft;
						}
						else
						{
							lTemp = lStack.top();
							lStack.pop();
							lFile << lTemp->sData->sNombre << " " << lTemp->sData->sApellido << " " << lTemp->sData->sFNac << " " << lTemp->sData->sSalario << endl;  //En lugar de un cout hacer un delete y antes verificar si el lTemp igual al aRoot
							lTemp = lTemp->sRgt;
						}
						break;
					}
					case Orden::desc:
					{
						if (lTemp)
						{
							lStack.push(lTemp);
							lTemp = lTemp->sRgt;
						}
						else
						{
							lTemp = lStack.top();
							lStack.pop();
							lFile << lTemp->sData->sNombre << " " << lTemp->sData->sApellido << " " << lTemp->sData->sFNac << " " << lTemp->sData->sSalario << endl;
							lTemp = lTemp->sLft;
						}
						break;
					}
					case Orden::sinorden:
					{
						if (lTemp)
						{
							lFile << lTemp->sData->sNombre << " " << lTemp->sData->sApellido << " " << lTemp->sData->sFNac << " " << lTemp->sData->sSalario << endl;
							lStack.push(lTemp);
							lTemp = lTemp->sLft;
						}
						else
						{
							lTemp = lStack.top();
							lStack.pop();
							lTemp = lTemp->sRgt;
						}
						break;
					}
					}
				}
				break;
			}
			}


			lFile.close();
		}

	}
}



PTNODE Arbol::getNewNode(PDATA pData)
{
	PTNODE lTemp = new TNODE;
	if (lTemp)
	{
		lTemp->sData = pData;
		lTemp->sLft = NULL;
		lTemp->sRgt = NULL;
		lTemp->sFrec = 1;
	}
	return lTemp;

}






DList::DList(tipo_Arbol pTipo_Arboles, bool pFrec)
{
	aHead = NULL;
	aTail = NULL;
	aCurr = NULL;
	aFrec = pFrec;

	aINom = new Arbol(ECampos::nombre,pTipo_Arboles);
	aIApe = new Arbol(ECampos::apellido, pTipo_Arboles);
	aIFNa = new Arbol(ECampos::fnac, pTipo_Arboles);
	aISal = new Arbol(ECampos::salario, pTipo_Arboles);
} // Constructor

DList::~DList(void)
{
	clean();

	if (aINom) delete aINom;
	if (aIApe) delete aIApe;
	if (aIFNa) delete aIFNa;
	if (aISal) delete aISal;

	// cout << "Bye!" << endl;
} // Destructor

void DList::clean(void)
{
	while (aHead) {
		PDNODE lTemp = aHead->sNext;
		if (aHead->sData)
			delete aHead->sData;
		delete aHead;
		aHead = lTemp;
	}

	aHead = NULL;
	aTail = NULL;
	aCurr = NULL;
} // clean

/*void DList::push_front(string pNombre)
{
	if (aHead == NULL) {
		aHead = getNewNode(pNombre);
		aTail = aHead;
	}
	else {
		bool lDo = true;
		if (aFrec) {
			if (pNombre == aHead->sNombre) {
				(aHead->sFrec)++;
				lDo = false;
			}
			else {
				PDNODE lItem = find(pNombre);
				if (lItem != NULL) {
					(lItem->sFrec)++;
					lDo = false;
				}
			}
		}
		if (lDo) {
			PDNODE lTemp = getNewNode(pNombre);
			aHead->sPrev = lTemp;
			lTemp->sNext = aHead;
			aHead = lTemp;
		}
	}
} // push_front*/

void DList::push_back(string pNombre, string pApellido,
	string pFNac, double pSalario)
{
	if (aHead == NULL) {
		aHead = getNewNode(pNombre, pApellido, pFNac, pSalario);
		aTail = aHead;

		aINom->push(aHead->sData);
		aIApe->push(aHead->sData);
		aIFNa->push(aHead->sData);
		aISal->push(aHead->sData);
	}
	else {
		/*bool lDo = true;
		if (aFrec) {
			if (pNombre == aTail->sNombre) {
				(aTail->sFrec)++;
				lDo = false;
			}
			else {
				PDNODE lItem = find(pNombre);
				if (lItem != NULL) {
					(lItem->sFrec)++;
					lDo = false;
				}
			}
		}
		if (lDo) {*/
		PDNODE lTemp = getNewNode(pNombre, pApellido, pFNac, pSalario);
		aTail->sNext = lTemp;
		lTemp->sPrev = aTail;
		aTail = lTemp;

		aINom->push(lTemp->sData);
		aIApe->push(lTemp->sData);
		aIFNa->push(lTemp->sData);
		aISal->push(lTemp->sData);
		//}
	}
} // push_back

/*void DList::push(string pNombre)
{
	if (aHead == NULL) {
		aHead = getNewNode(pNombre);
		aTail = aHead;
	}
	else {
		if (pNombre <= aHead->sNombre)
			push_front(pNombre);
		else if (pNombre >= aTail->sNombre)
			push_back(pNombre);
		else {
			PDNODE lItem = search(pNombre);
			if (lItem) {
				if (aFrec && (lItem->sNombre == pNombre)) {
					(lItem->sFrec)++;
				}
				else {
					PDNODE lTemp = getNewNode(pNombre);
					lTemp->sNext = lItem;
					lTemp->sPrev = lItem->sPrev;
					lItem->sPrev->sNext = lTemp;
					lItem->sPrev = lTemp;
				}
			}
		}
	}
} // push*/

/*PDNODE DList::top_front(void)
{
	if (aHead) {
		return aHead;
	}
	return NULL;
} // top_front*/

/*PDNODE DList::top_back(void)
{
	if (aHead) {
		return aTail;
	}
	return NULL;
} // top_back*/

/*
PDATA DList::get(ECampos pCampo, bool pRev)
{
	PDATA lTemp = NULL;

	switch (pCampo) {
	case ECampos::nombre: lTemp = aINom->get(pRev); break;
	case ECampos::apellido: lTemp = aIApe->get(pRev); break;
	case ECampos::fnac: lTemp = aIFNa->get(pRev); break;
	case ECampos::salario: lTemp = aISal->get(pRev); break;
	}

	return lTemp;
} // get
*/

void DList::pop_front(bool lDeleteIndexes)
{
	if (aHead)
	{
		PDNODE lTemp = aHead->sNext;
		bool lEqual = (aHead == aCurr);
		if (lDeleteIndexes)
		{
			aINom->delr(lTemp->sData);
			aIApe->delr(lTemp->sData);
			aIFNa->delr(lTemp->sData);
			aISal->delr(lTemp->sData);
		}
		delete aHead->sData;
		delete aHead;
		aHead = lTemp;
		if (aHead) {
			aHead->sPrev = NULL;
			aCurr = (lEqual ? aHead : aCurr);
		}
		else {
			aTail = NULL;
			aCurr = NULL;
		}
	}
} // pop_front

void DList::pop_back(bool lDeleteIndexes)
{
	if (aHead)
	{
		PDNODE lTemp = aTail->sPrev;
		bool lEqual = (aTail == aCurr);
		if (lDeleteIndexes)
		{
			aINom->delr(lTemp->sData);
			aIApe->delr(lTemp->sData);
			aIFNa->delr(lTemp->sData);
			aISal->delr(lTemp->sData);
		}
		delete aTail->sData;
		delete aTail;
		aTail = lTemp;
		if (aTail) {
			aTail->sNext = NULL;
			aCurr = (lEqual ? aTail : aCurr);
		}
		else {
			aHead = NULL;
			aCurr = NULL;
		}
	}
} // pop_back

void DList::del(string pNombre, string pApellido, string pFNac, double pSalario)
{
	if (aHead)
	{
		PDNODE lTemp = NULL;
		if ((pNombre == aHead->sData->sNombre) && (pApellido == aHead->sData->sApellido) && (pFNac == aHead->sData->sFNac) && (pSalario == aHead->sData->sSalario))
		{
			lTemp = aHead;
		}
		else if ((pNombre == aHead->sData->sNombre) && (pApellido == aHead->sData->sApellido) && (pFNac == aHead->sData->sFNac) && (pSalario == aHead->sData->sSalario))
		{
			lTemp = aTail;
		}
		else
		{
			lTemp = find(pNombre, pApellido, pFNac, pSalario);
		}

		if (lTemp)
		{
			aINom->delr(lTemp->sData);
			aIApe->delr(lTemp->sData);
			aIFNa->delr(lTemp->sData);
			aISal->delr(lTemp->sData);
			if (lTemp == aHead)
			{
				pop_front();
			}
			else if (lTemp == aTail)
			{
				pop_back();
			}
			else
			{
				delete lTemp->sData;
				lTemp->sPrev->sNext = lTemp->sNext;
				lTemp->sNext->sPrev = lTemp->sPrev;
				delete lTemp;
			}
		}
	}
} // del

bool DList::isEmpty(void)
{
	return (aHead == NULL);
} // isEmpty

void DList::repr(ECampos pCampo, bool pRev)
{
	if (aHead) {
		switch (pCampo) 
		{
		case ECampos::nombre: 
		{
			if (pRev == false)
			{
				aINom->repr();
			}
			else
			{
				aINom->repr(Orden::desc);
			}
			break;
		}
		case ECampos::apellido: {
			if (pRev == false)
			{
				aIApe->repr();
			}
			else
			{
				aIApe->repr(Orden::desc);
			}
			break;
		}
		case ECampos::fnac: 
		{	
			if (pRev == false)
			{
				aIFNa->repr();
			}
			else
			{
				aIFNa->repr(Orden::desc);
			}
			break;
		}
		case ECampos::salario: 
		{
			if (pRev == false)
			{
				aISal->repr();
			}
			else
			{
				aISal->repr(Orden::desc);
			}
			break;
		}

		}
	}
} // repr

/*void DList::read(string pPath, char pMethod)
{
	auto lStart = chrono::high_resolution_clock::now();
	string lLine = "";
	ifstream lFile(pPath);

	while (getline(lFile, lLine)) {
		switch (pMethod) {
		case 'b':
			push_back(lLine);
			break;
		case 'f':
			push_front(lLine);
			break;
		default:
			push(lLine);
			break;
		}
	}

	lFile.close();

	auto lElapsed = chrono::high_resolution_clock::now() - lStart;
	long long lMS = chrono::duration_cast<chrono::microseconds>
		(lElapsed).count();
	cout << lMS << " ms" << endl;
} // read*/

/*void DList::write(string pPath, bool pRev)
{
	if (aHead) {
		ofstream lFile(pPath);
		if (lFile.is_open()) {
			PDNODE lTemp = (pRev == false ? aHead : aTail);
			while (lTemp) {
				lFile << lTemp->sNombre << endl;
				lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
			}
			lFile.close();
		}
	}
} // write*/

PDNODE DList::find(string pNombre, string pApellido, string pFNac, double pSalario)
{
	if (aHead)
	{
		PDNODE lTemp = aHead;
		while (lTemp)
		{
			if ((pNombre == lTemp->sData->sNombre) && (pApellido == lTemp->sData->sApellido) && (pFNac == lTemp->sData->sFNac) && (pSalario == lTemp->sData->sSalario))
			{
				return lTemp;
			}
			lTemp = lTemp->sNext;
		}
	}
	return NULL;
} // find

/*PDNODE DList::search(string pNombre)
{
	PDNODE lTemp = aHead;

	while (lTemp) {
		if (pNombre <= lTemp->sNombre)
			return lTemp;
		lTemp = lTemp->sNext;
	}

	return NULL;
} // search*/

PDNODE DList::getNewNode(string pNombre, string pApellido,
	string pFNac, double pSalario)
{
	PDNODE lTemp = new DNODE;

	if (lTemp) {
		lTemp->sData = new DATA;
		if (lTemp->sData) {
			lTemp->sData->sNombre = pNombre;
			lTemp->sData->sApellido = pApellido;
			lTemp->sData->sFNac = pFNac;
			lTemp->sData->sSalario = pSalario;
		}
		lTemp->sFrec = 1;
		lTemp->sNext = NULL;
		lTemp->sPrev = NULL;
	}

	return lTemp;
} // getNewNode
