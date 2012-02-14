/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativeinstruction_p.h"

#include "qdeclarativecompiler_p.h"

#include <QtCore/qdebug.h>

QT_BEGIN_NAMESPACE

void QDeclarativeCompiledData::dump(QDeclarativeInstruction *instr, int idx)
{
#ifdef QT_NO_DEBUG_STREAM
    Q_UNUSED(instr)
    Q_UNUSED(idx)
#else
    switch (instructionType(instr)) {
    case QDeclarativeInstruction::Init:
        qWarning().nospace() << idx << "\t\t" << "INIT\t\t\t" << instr->init.bindingsSize << "\t" << instr->init.parserStatusSize << "\t" << instr->init.contextCache << "\t" << instr->init.compiledBinding;
        break;
    case QDeclarativeInstruction::DeferInit:
        qWarning().nospace() << idx << "\t\t" << "DEFER_INIT\t\t" << instr->deferInit.bindingsSize << "\t" << instr->deferInit.parserStatusSize;
        break;
    case QDeclarativeInstruction::Done:
        qWarning().nospace() << idx << "\t\t" << "DONE";
        break;
    case QDeclarativeInstruction::CreateCppObject:
        qWarning().nospace() << idx << "\t\t" << "CREATECPP\t\t\t" << instr->create.type << "\t\t\t" << types.at(instr->create.type).className;
        break;
    case QDeclarativeInstruction::CreateQMLObject:
        qWarning().nospace() << idx << "\t\t" << "CREATEQML\t\t\t" << instr->createQml.type << "\t" << instr->createQml.bindingBits << "\t\t" << types.at(instr->createQml.type).className;
        break;
    case QDeclarativeInstruction::CompleteQMLObject:
        qWarning().nospace() << idx << "\t\t" << "COMPLETEQML";
        break;
    case QDeclarativeInstruction::CreateSimpleObject:
        qWarning().nospace() << idx << "\t\t" << "CREATE_SIMPLE\t\t" << instr->createSimple.typeSize;
        break;
    case QDeclarativeInstruction::SetId:
        qWarning().nospace() << idx << "\t\t" << "SETID\t\t\t" << instr->setId.value << "\t\t\t" << primitives.at(instr->setId.value);
        break;
    case QDeclarativeInstruction::SetDefault:
        qWarning().nospace() << idx << "\t\t" << "SET_DEFAULT";
        break;
    case QDeclarativeInstruction::CreateComponent:
        qWarning().nospace() << idx << "\t\t" << "CREATE_COMPONENT\t" << instr->createComponent.count;
        break;
    case QDeclarativeInstruction::StoreMetaObject:
        qWarning().nospace() << idx << "\t\t" << "STORE_META\t\t" << instr->storeMeta.data;
        break;
    case QDeclarativeInstruction::StoreFloat:
        qWarning().nospace() << idx << "\t\t" << "STORE_FLOAT\t\t" << instr->storeFloat.propertyIndex << "\t" << instr->storeFloat.value;
        break;
    case QDeclarativeInstruction::StoreDouble:
        qWarning().nospace() << idx << "\t\t" << "STORE_DOUBLE\t\t" << instr->storeDouble.propertyIndex << "\t" << instr->storeDouble.value;
        break;
    case QDeclarativeInstruction::StoreDoubleQList:
        qWarning().nospace() << idx << "\t\t" << "STORE_DOUBLE_QLIST\t\t" << instr->storeDouble.propertyIndex << "\t" << instr->storeDouble.value;
        break;
    case QDeclarativeInstruction::StoreInteger:
        qWarning().nospace() << idx << "\t\t" << "STORE_INTEGER\t\t" << instr->storeInteger.propertyIndex << "\t" << instr->storeInteger.value;
        break;
    case QDeclarativeInstruction::StoreIntegerQList:
        qWarning().nospace() << idx << "\t\t" << "STORE_INTEGER_QLIST\t\t" << instr->storeInteger.propertyIndex << "\t" << instr->storeInteger.value;
        break;
    case QDeclarativeInstruction::StoreBool:
        qWarning().nospace() << idx << "\t\t" << "STORE_BOOL\t\t" << instr->storeBool.propertyIndex << "\t" << instr->storeBool.value;
        break;
    case QDeclarativeInstruction::StoreBoolQList:
        qWarning().nospace() << idx << "\t\t" << "STORE_BOOL_QLIST\t\t" << instr->storeBool.propertyIndex << "\t" << instr->storeBool.value;
        break;
    case QDeclarativeInstruction::StoreString:
        qWarning().nospace() << idx << "\t\t" << "STORE_STRING\t\t" << instr->storeString.propertyIndex << "\t" << instr->storeString.value << "\t\t" << primitives.at(instr->storeString.value);
        break;
    case QDeclarativeInstruction::StoreStringList:
        qWarning().nospace() << idx << "\t\t" << "STORE_STRINGLIST\t\t" << instr->storeString.propertyIndex << "\t" << instr->storeString.value << "\t\t" << primitives.at(instr->storeString.value);
        break;
    case QDeclarativeInstruction::StoreStringQList:
        qWarning().nospace() << idx << "\t\t" << "STORE_STRING_QLIST\t\t" << instr->storeString.propertyIndex << "\t" << instr->storeString.value << "\t\t" << primitives.at(instr->storeString.value);
        break;
    case QDeclarativeInstruction::StoreTrString:
        qWarning().nospace() << idx << "\t\t" << "STORE_TR_STRING\t" << instr->storeTrString.propertyIndex << "\t" << instr->storeTrString.context << "\t" << instr->storeTrString.text << "\t" << instr->storeTrString.comment << "\t" << instr->storeTrString.n;
        break;
    case QDeclarativeInstruction::StoreTrIdString:
        qWarning().nospace() << idx << "\t\t" << "STORE_TRID_STRING\t" << instr->storeTrIdString.propertyIndex << "\t" << instr->storeTrIdString.text << "\t" << instr->storeTrIdString.n;
        break;
    case QDeclarativeInstruction::StoreByteArray:
        qWarning().nospace() << idx << "\t\t" << "STORE_BYTEARRAY" << instr->storeByteArray.propertyIndex << "\t" << instr->storeByteArray.value << "\t\t" << datas.at(instr->storeByteArray.value);
        break;
    case QDeclarativeInstruction::StoreUrl:
        qWarning().nospace() << idx << "\t\t" << "STORE_URL\t\t" << instr->storeUrl.propertyIndex << "\t" << instr->storeUrl.value << "\t\t" << urls.at(instr->storeUrl.value);
        break;
    case QDeclarativeInstruction::StoreUrlQList:
        qWarning().nospace() << idx << "\t\t" << "STORE_URL_QLIST\t\t" << instr->storeUrl.propertyIndex << "\t" << instr->storeUrl.value << "\t\t" << urls.at(instr->storeUrl.value);
        break;
    case QDeclarativeInstruction::StoreColor:
        qWarning().nospace() << idx << "\t\t" << "STORE_COLOR\t\t" << instr->storeColor.propertyIndex << "\t\t\t" << QString::number(instr->storeColor.value, 16);
        break;
    case QDeclarativeInstruction::StoreDate:
        qWarning().nospace() << idx << "\t\t" << "STORE_DATE\t\t" << instr->storeDate.propertyIndex << "\t" << instr->storeDate.value;
        break;
    case QDeclarativeInstruction::StoreTime:
        qWarning().nospace() << idx << "\t\t" << "STORE_TIME\t\t" << instr->storeTime.propertyIndex;
        break;
    case QDeclarativeInstruction::StoreDateTime:
        qWarning().nospace() << idx << "\t\t" << "STORE_DATETIME\t\t" << instr->storeDateTime.propertyIndex;
        break;
    case QDeclarativeInstruction::StorePoint:
        qWarning().nospace() << idx << "\t\t" << "STORE_POINT\t\t" << instr->storePoint.propertyIndex << "\t" << instr->storePoint.point.xp << "\t" << instr->storePoint.point.yp;
        break;
    case QDeclarativeInstruction::StorePointF:
        qWarning().nospace() << idx << "\t\t" << "STORE_POINTF\t\t" << instr->storePointF.propertyIndex << "\t" << instr->storePointF.point.xp << "\t" << instr->storePointF.point.yp;
        break;
    case QDeclarativeInstruction::StoreSize:
        qWarning().nospace() << idx << "\t\t" << "STORE_SIZE\t\t" << instr->storeSize.propertyIndex << "\t" << instr->storeSize.size.wd << "\t" << instr->storeSize.size.ht;
        break;
    case QDeclarativeInstruction::StoreSizeF:
        qWarning().nospace() << idx << "\t\t" << "STORE_SIZEF\t\t" << instr->storeSizeF.propertyIndex << "\t" << instr->storeSizeF.size.wd << "\t" << instr->storeSizeF.size.ht;
        break;
    case QDeclarativeInstruction::StoreRect:
        qWarning().nospace() << idx << "\t\t" << "STORE_RECT\t\t" << instr->storeRect.propertyIndex << "\t" << instr->storeRect.rect.x1 << "\t" << instr->storeRect.rect.y1 << "\t" << instr->storeRect.rect.x2 << "\t" << instr->storeRect.rect.y2;
        break;
    case QDeclarativeInstruction::StoreRectF:
        qWarning().nospace() << idx << "\t\t" << "STORE_RECTF\t\t" << instr->storeRectF.propertyIndex << "\t" << instr->storeRectF.rect.xp << "\t" << instr->storeRectF.rect.yp << "\t" << instr->storeRectF.rect.w << "\t" << instr->storeRectF.rect.h;
        break;
    case QDeclarativeInstruction::StoreVector3D:
        qWarning().nospace() << idx << "\t\t" << "STORE_VECTOR3D\t\t" << instr->storeVector3D.propertyIndex << "\t" << instr->storeVector3D.vector.xp << "\t" << instr->storeVector3D.vector.yp << "\t" << instr->storeVector3D.vector.zp;
        break;
    case QDeclarativeInstruction::StoreVector4D:
        qWarning().nospace() << idx << "\t\t" << "STORE_VECTOR4D\t\t" << instr->storeVector4D.propertyIndex << "\t" << instr->storeVector4D.vector.xp << "\t" << instr->storeVector4D.vector.yp << "\t" << instr->storeVector4D.vector.zp << "\t" << instr->storeVector4D.vector.wp;
        break;
    case QDeclarativeInstruction::StoreVariant:
        qWarning().nospace() << idx << "\t\t" << "STORE_VARIANT\t\t" << instr->storeString.propertyIndex << "\t" << instr->storeString.value << "\t\t" << primitives.at(instr->storeString.value);
        break;
    case QDeclarativeInstruction::StoreVariantInteger:
        qWarning().nospace() << idx << "\t\t" << "STORE_VARIANT_INTEGER\t\t" << instr->storeInteger.propertyIndex << "\t" << instr->storeInteger.value;
        break;
    case QDeclarativeInstruction::StoreVariantDouble:
        qWarning().nospace() << idx << "\t\t" << "STORE_VARIANT_DOUBLE\t\t" << instr->storeDouble.propertyIndex << "\t" << instr->storeDouble.value;
        break;
    case QDeclarativeInstruction::StoreVariantBool:
        qWarning().nospace() << idx << "\t\t" << "STORE_VARIANT_BOOL\t\t" << instr->storeBool.propertyIndex << "\t" << instr->storeBool.value;
        break;
    case QDeclarativeInstruction::StoreObject:
        qWarning().nospace() << idx << "\t\t" << "STORE_OBJECT\t\t" << instr->storeObject.propertyIndex;
        break;
    case QDeclarativeInstruction::StoreVariantObject:
        qWarning().nospace() << idx << "\t\t" << "STORE_VARIANT_OBJECT\t" << instr->storeObject.propertyIndex;
        break;
    case QDeclarativeInstruction::StoreInterface:
        qWarning().nospace() << idx << "\t\t" << "STORE_INTERFACE\t\t" << instr->storeObject.propertyIndex;
        break;
    case QDeclarativeInstruction::StoreSignal:
        qWarning().nospace() << idx << "\t\t" << "STORE_SIGNAL\t\t" << instr->storeSignal.signalIndex << "\t" << instr->storeSignal.value << "\t\t" << primitives.at(instr->storeSignal.value);
        break;
    case QDeclarativeInstruction::StoreImportedScript:
        qWarning().nospace() << idx << "\t\t" << "STORE_IMPORTED_SCRIPT\t" << instr->storeScript.value;
        break;
    case QDeclarativeInstruction::StoreScriptString:
        qWarning().nospace() << idx << "\t\t" << "STORE_SCRIPT_STRING\t" << instr->storeScriptString.propertyIndex << "\t" << instr->storeScriptString.value << "\t" << instr->storeScriptString.scope << "\t" << instr->storeScriptString.bindingId;
        break;
    case QDeclarativeInstruction::AssignSignalObject:
        qWarning().nospace() << idx << "\t\t" << "ASSIGN_SIGNAL_OBJECT\t" << instr->assignSignalObject.signal << "\t\t\t" << primitives.at(instr->assignSignalObject.signal);
        break;
    case QDeclarativeInstruction::AssignCustomType:
        qWarning().nospace() << idx << "\t\t" << "ASSIGN_CUSTOMTYPE\t" << instr->assignCustomType.propertyIndex << "\t" << instr->assignCustomType.primitive << "\t" << instr->assignCustomType.type;
        break;
    case QDeclarativeInstruction::InitV8Bindings:
        qWarning().nospace() << idx << "\t\t" << "INIT_V8_BINDING\t" << instr->initV8Bindings.programIndex << "\t" << instr->initV8Bindings.line;
        break;
    case QDeclarativeInstruction::StoreBinding:
        qWarning().nospace() << idx << "\t\t" << "STORE_BINDING\t" << instr->assignBinding.property.coreIndex << "\t" << instr->assignBinding.value << "\t" << instr->assignBinding.context;
        break;
    case QDeclarativeInstruction::StoreBindingOnAlias:
        qWarning().nospace() << idx << "\t\t" << "STORE_BINDING_ALIAS\t" << instr->assignBinding.property.coreIndex << "\t" << instr->assignBinding.value << "\t" << instr->assignBinding.context;
        break;
    case QDeclarativeInstruction::StoreV4Binding:
        qWarning().nospace() << idx << "\t\t" << "STORE_COMPILED_BINDING\t" << instr->assignV4Binding.property << "\t" << instr->assignV4Binding.value << "\t" << instr->assignV4Binding.context;
        break;
    case QDeclarativeInstruction::StoreV8Binding:
        qWarning().nospace() << idx << "\t\t" << "STORE_V8_BINDING\t" << instr->assignBinding.property.coreIndex << "\t" << instr->assignBinding.value << "\t" << instr->assignBinding.context;
        break;
    case QDeclarativeInstruction::StoreValueSource:
        qWarning().nospace() << idx << "\t\t" << "STORE_VALUE_SOURCE\t" << instr->assignValueSource.property.coreIndex << "\t" << instr->assignValueSource.castValue;
        break;
    case QDeclarativeInstruction::StoreValueInterceptor:
        qWarning().nospace() << idx << "\t\t" << "STORE_VALUE_INTERCEPTOR\t" << instr->assignValueInterceptor.property.coreIndex << "\t" << instr->assignValueInterceptor.castValue;
        break;
    case QDeclarativeInstruction::BeginObject:
        qWarning().nospace() << idx << "\t\t" << "BEGIN\t\t\t" << instr->begin.castValue;
        break;
    case QDeclarativeInstruction::StoreObjectQList:
        qWarning().nospace() << idx << "\t\t" << "STORE_OBJECT_QLIST";
        break;
    case QDeclarativeInstruction::AssignObjectList:
        qWarning().nospace() << idx << "\t\t" << "ASSIGN_OBJECT_LIST";
        break;
    case QDeclarativeInstruction::FetchAttached:
        qWarning().nospace() << idx << "\t\t" << "FETCH_ATTACHED\t\t" << instr->fetchAttached.id;
        break;
    case QDeclarativeInstruction::FetchQList:
        qWarning().nospace() << idx << "\t\t" << "FETCH_QLIST\t\t" << instr->fetch.property;
        break;
    case QDeclarativeInstruction::FetchObject:
        qWarning().nospace() << idx << "\t\t" << "FETCH\t\t\t" << instr->fetch.property;
        break;
    case QDeclarativeInstruction::FetchValueType:
        qWarning().nospace() << idx << "\t\t" << "FETCH_VALUE\t\t" << instr->fetchValue.property << "\t" << instr->fetchValue.type << "\t" << instr->fetchValue.bindingSkipList;
        break;
    case QDeclarativeInstruction::PopFetchedObject:
        qWarning().nospace() << idx << "\t\t" << "POP";
        break;
    case QDeclarativeInstruction::PopQList:
        qWarning().nospace() << idx << "\t\t" << "POP_QLIST";
        break;
    case QDeclarativeInstruction::PopValueType:
        qWarning().nospace() << idx << "\t\t" << "POP_VALUE\t\t" << instr->fetchValue.property << "\t" << instr->fetchValue.type;
        break;
    case QDeclarativeInstruction::Defer:
        qWarning().nospace() << idx << "\t\t" << "DEFER" << "\t\t\t" << instr->defer.deferCount;
        break;
    default:
        qWarning().nospace() << idx << "\t\t" << "XXX UNKNOWN INSTRUCTION" << "\t" << instructionType(instr);
        break;
    }
#endif // QT_NO_DEBUG_STREAM
}

int QDeclarativeInstruction::size(Type type)
{
#define QML_RETURN_INSTR_SIZE(I, FMT) case I: return QDeclarativeInstructionMeta<(int)I>::Size;
    switch (type) {
    FOR_EACH_QML_INSTR(QML_RETURN_INSTR_SIZE)
    default: return 0;
    }
#undef QML_RETURN_INSTR_SIZE
}

QT_END_NAMESPACE
