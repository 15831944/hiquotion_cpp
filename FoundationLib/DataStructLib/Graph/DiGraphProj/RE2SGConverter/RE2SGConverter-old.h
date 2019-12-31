// RE2SGConverter.h: interface for the CRE2SGConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RE2SGCONVERTER_H__E8D483D2_5949_487B_A549_573E84F3BA39__INCLUDED_)
#define AFX_RE2SGCONVERTER_H__E8D483D2_5949_487B_A549_573E84F3BA39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\EmptyRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\RangeRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\SymbolRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\ConcatRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\OrRegularExpression.h"
#include "..\..\..\..\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStarRegularExpression.h"

template <class NodeData, class ArcWeight>
class CRE2SGConverter  
{
public:
	CRE2SGConverter(){};
	virtual ~CRE2SGConverter(){};

	static CStatusGraphic<NodeData, ArcWeight> *genFromEmptyRE(CEmptyRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromRangeRE(CRangeRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromSymbolRE(CSymbolRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromConcatRE(CConcatRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromOrRE(COrRegularExpression *re);
	static CStatusGraphic<NodeData, ArcWeight> *genFromKleenStarRE(CKleenStarRegularExpression *re);

	CStatusGraphic *genFromEmptyRE(CEmptyRegularExpression *re)
	{
		if(!re)
			return NULL;

		CStatusGraphic *graphic=new CStatusGraphic();
		CArc *arc=new CArc();  // Ȩ��Ϊ���ַ��ı�
		
	// 	graphic->getStartNode()->setArcFirstOut(arc);
	// 	graphic->getEndNode()->setArcFirstIn(arc);

		arc->setNodeStart(graphic->getStartNode());
		arc->setNodeEnd(graphic->getEndNode());
	// 	arc->setNextArcOutFromStart(NULL);
	// 	arc->setNextArcToEnd(NULL);

		return graphic;
	}

	CStatusGraphic *genFromRangeRE(CRangeRegularExpression *re)
	{
		if(!re)
			return NULL;
		
		CStatusGraphic *graphic=new CStatusGraphic();
		CArc *arc=new CArc();  // Ȩ��Ϊ�ַ���Χ�ıߣ������������ı�
		CArcWeight *weight=new CArcWeight();
		weight->setChecker(re->getChecker());
		arc->setWeight(weight);

		arc->setNodeStart(graphic->getStartNode());
		arc->setNodeEnd(graphic->getEndNode());
	// 	arc->setNextArcOutFromStart(NULL);
	// 	arc->setNextArcToEnd(NULL);
		
		return graphic;
	}

	CStatusGraphic *genFromSymbolRE(CSymbolRegularExpression *re)
	{
		if(!re)
			return NULL;
		
		CStatusGraphic *graphic=new CStatusGraphic();
		CArc *arc=new CArc();  // Ȩ��Ϊ���ַ��ı�
		CArcWeight *weight=new CArcWeight();
		weight->setChecker(re->getChecker());
		arc->setWeight(weight);
		
		arc->setNodeStart(graphic->getStartNode());
		arc->setNodeEnd(graphic->getEndNode());
	// 	arc->setNextArcOutFromStart(NULL);
	// 	arc->setNextArcToEnd(NULL);
		
		return graphic;
	}

	CStatusGraphic *genFromConcatRE(CConcatRegularExpression *re)
	{
		if(!re)
			return NULL;

		if(!re->getRegularExpression1() || !re->getRegularExpression2())
			return NULL;
		
		// �½�״̬ͼ
		CStatusGraphic *graphic=new CStatusGraphic();

		// ��re�л�ȡ�������ʽ��״̬ͼ
		CStatusGraphic *sg1=re->getRegularExpression1()->genStatusGraphic();
		CStatusGraphic *sg2=re->getRegularExpression2()->genStatusGraphic();

		// ԭ��һ��״̬ͼ�Ŀ�ʼ�ڵ���Ϊ��ͼ�Ŀ�ʼ�ڵ㣬�ڶ�״̬ͼ���յ���Ϊ��ͼ���ս�ڵ�
		graphic->setStartNode(sg1->getStartNode());
		sg1->setStartNodeDestroy(FALSE);
		graphic->setEndNode(sg2->getEndNode());
		sg2->setEndNodeDestroy(FALSE);

		// ������״̬ͼ�еĽڵ�ͱߣ���ӵ��½���״̬ͼ graphic ��
		graphic->addNodes(sg1->getNodes());
		sg1->setNodesDestroy(FALSE);  // gStart ������ʱ�����������ڲ��Ľڵ��б���Ϊ��Щ�ڵ��Ѿ�ת�Ƶ� graphic ͼ���ˣ���ͬ��
		graphic->addNode(sg1->getEndNode());
		sg1->setEndNodeDestroy(FALSE);
		graphic->addArcs(sg1->getArcs());
		sg1->setArcsDestroy(FALSE);

		graphic->addNodes(sg2->getNodes());
		sg2->setNodesDestroy(FALSE);
		graphic->addNode(sg2->getStartNode());
		sg2->setStartNodeDestroy(FALSE);
		graphic->addArcs(sg2->getArcs());
		sg2->setArcsDestroy(FALSE);

		// ���ӵ�һ��״̬ͼ���ս�ڵ���ڶ���״̬ͼ�Ŀ�ʼ��������
		CArc *arc=new CArc();  // Ȩ��Ϊ���ַ��ı�
		arc->setNodeStart(sg1->getEndNode());
		arc->setNodeEnd(sg2->getStartNode());
	// 	arc->setNextArcOutFromStart(NULL);
	// 	arc->setNextArcToEnd(NULL);
		
		// ����һ��״̬ͼ���ս�ڵ���ӳ���
		CNode *node=sg1->getEndNode();
		if(node)
			node->addArcOut(arc);
		// ���ڶ���״̬ͼ�Ŀ�ʼ�ڵ�������
		node=sg2->getStartNode();
		if(node)
			node->addArcIn(arc);

		// �ͷ�ԭ״̬ͼ�ڴ�
		delete sg1;
		delete sg2;
		
		return graphic;
	}

	CStatusGraphic *genFromOrRE(COrRegularExpression *re)
	{
		if(!re)
			return NULL;
		
		if(!re->getRegularExpression1() || !re->getRegularExpression2())
			return NULL;
		
		// �½�״̬ͼ
		CStatusGraphic *graphic=new CStatusGraphic();
		
		// ��re�л�ȡ�������ʽ��״̬ͼ
		CStatusGraphic *sg1=re->getRegularExpression1()->genStatusGraphic();
		CStatusGraphic *sg2=re->getRegularExpression2()->genStatusGraphic();

		// ��ԭ����״̬ͼ�Ľڵ�ͱ���ӵ���״̬ͼ��
		// ������ԭ����״̬ͼ�Ľڵ�ͱ߲�������
		graphic->addNode(sg1->getStartNode());
		graphic->addNodes(sg1->getNodes());
		graphic->addNode(sg1->getEndNode());

		sg1->setNodesDestroy(FALSE);
		sg1->setStartNodeDestroy(FALSE);
		sg1->setEndNodeDestroy(FALSE);

		graphic->addNode(sg2->getStartNode());
		graphic->addNodes(sg2->getNodes());
		graphic->addNode(sg2->getEndNode());

		sg2->setNodesDestroy(FALSE);
		sg2->setStartNodeDestroy(FALSE);
		sg2->setEndNodeDestroy(FALSE);
		
		graphic->addArcs(sg1->getArcs());
		graphic->addArcs(sg2->getArcs());

		sg1->setArcsDestroy(FALSE);
		sg2->setArcsDestroy(FALSE);

		// ����״̬ͼ����ʼ�ڵ㻮�������߷ֱ�����������ʽ����״̬ͼ�Ŀ�ʼ�ڵ�
		CArc *arcToG1=new CArc();
		CArc *arcToG2=new CArc();
		
		arcToG1->setNodeStart(graphic->getStartNode());
		arcToG1->setNodeEnd(sg1->getStartNode());
		CNode *node=graphic->getStartNode();
		if(node)
			node->addArcOut(arcToG1);
		node=sg1->getStartNode();
		if(node)
			node->addArcIn(arcToG1);

		arcToG2->setNodeStart(graphic->getStartNode());
		arcToG2->setNodeEnd(sg2->getStartNode());
		node=graphic->getStartNode();
		if(node)
			node->addArcOut(arcToG2);
		node=sg2->getStartNode();
		if(node)
			node->addArcIn(arcToG2);

		graphic->addArc(arcToG1);
		graphic->addArc(arcToG2);

		// ��ԭ״̬ͼ��������ֹ�ڵ㻮�������ߣ�����״̬ͼ����ֹ�ڵ�
		CArc *arcFromG1=new CArc();
		CArc *arcFromG2=new CArc();

		arcFromG1->setNodeStart(sg1->getEndNode());
		arcFromG1->setNodeEnd(graphic->getEndNode());
		node=sg1->getEndNode();
		if(node)
			node->addArcOut(arcFromG1);
		node=graphic->getEndNode();
		if(node)
			node->addArcIn(arcFromG1);

		arcFromG2->setNodeStart(sg2->getEndNode());
		arcFromG2->setNodeEnd(graphic->getEndNode());
		node=sg2->getEndNode();
		if(node)
			node->addArcOut(arcFromG2);
		node=graphic->getEndNode();
		if(node)
			node->addArcIn(arcFromG2);

		graphic->addArc(arcFromG1);
		graphic->addArc(arcFromG2);

		// �ͷ�ԭ״̬ͼ�ڴ�
		delete sg1;
		delete sg2;
		
		return graphic;
	}

	CStatusGraphic *genFromKleenStarRE(CKleenStarRegularExpression *re)
	{
		CStatusGraphic *graphic=new CStatusGraphic();

		CStatusGraphic *sg=re->genStatusGraphic();

		// ���ԭ״̬ͼ�Ľڵ�ͱߵ���״̬ͼ��
		// ������ԭ״̬ͼ�Ľڵ�ͱ߲�������
		graphic->addNode(sg->getStartNode());
		graphic->addNodes(sg->getNodes());
		graphic->addNode(sg->getEndNode());

		sg->setStartNodeDestroy(FALSE);
		sg->setNodesDestroy(FALSE);
		sg->setEndNodeDestroy(FALSE);

		graphic->addArcs(sg->getArcs());
		sg->setArcsDestroy(FALSE);

		// ������״̬ͼ�Ŀ�ʼ�ڵ��ԭ״̬ͼ�Ŀ�ʼ�ڵ㣬��һ��epsilon�ı�
		CArc *arcStart=new CArc();
		arcStart->setNodeStart(graphic->getStartNode());
		arcStart->setNodeEnd(sg->getStartNode());
		CNode *node=graphic->getStartNode();
		if(node)
			node->addArcOut(arcStart);
		node=sg->getStartNode();
		if(node)
			node->addArcIn(arcStart);

		graphic->addArc(arcStart);

		// ����ԭ״̬ͼ����ֹ�ڵ����״̬ͼ����ֹ�ڵ㣬��һ��epsilon�ı�
		CArc *arcEnd=new CArc();
		arcEnd->setNodeStart(sg->getEndNode());
		arcEnd->setNodeEnd(graphic->getEndNode());
		node=sg->getEndNode();
		if(node)
			node->addArcOut(arcEnd);
		node=graphic->getEndNode();
		if(node)
			node->addArcIn(arcEnd);

		graphic->addArc(arcEnd);

		// ������״̬ͼ�Ŀ�ʼ����ֹ�ڵ㣬��һ��epsilon�ı�
		CArc *arc=new CArc();
		arc->setNodeStart(graphic->getStartNode());
		arc->setNodeEnd(graphic->getEndNode());
		node=graphic->getStartNode();
		if(node)
			node->addArcOut(arc);
		node=graphic->getEndNode();
		if(node)
			node->addArcIn(arc);

		// ������״̬ͼ����ֹ�ڵ��ԭ״̬ͼ�Ŀ�ʼ�ڵ㣬��һ���ߣ���Ҫ����Ȩ��
		CArc *arc2=new CArc();
		arc2->setNodeStart(graphic->getEndNode());
		arc2->setNodeEnd(sg->getStartNode());
		node=graphic->getEndNode();
		if(node)
			node->addArcOut(arc2);
		node=sg->getStartNode();
		if(node)
			node->addArcIn(arc2);

		CArcWeight *weight=new CArcWeight();
		weight->setChecker(re->getChecker());

		arc2->setWeight(weight);

		graphic->addArc(arc2);

		// �������ԭ״̬ͼ��ռ�ڴ�
		delete sg;
		
		return graphic;
	}
};

#endif // !defined(AFX_RE2SGCONVERTER_H__E8D483D2_5949_487B_A549_573E84F3BA39__INCLUDED_)
