**Usuário**

- _id_ (ObjectId)
- _nome_ (string)
- _email_ (string)
- _senha_ (string)
- _tipo_ (string)
- _dataCadastro_ (date)

**Receita**

- _id_ (ObjectId)
- _nome_ (string)
- _descricao_ (string)
- _tempoFermentacao_ (number)
- _tempoMaturacao_ (number)
- _ingredientes_ (array of objects)
- _ingrediente_ (ObjectId)
- _quantidade_ (number)
- _usuario_ (ObjectId)

**Ingrediente**

- _id_ (ObjectId)
- _nome_ (string)
- _tipo_ (string)
- _quantidadeEstoque_ (number)
- _unidadeMedida_ (string)

**Lote**

- _id_ (ObjectId)
- _numeroLote_ (number)
- _dataInicioProducao_ (date)
- _dataTerminoProducao_ (date)
- _receita_ (ObjectId)
- _quantidadeProduzida_ (number)
- _status_ (string)
- _temperatura_ (number)
- _sensores_ (array of ObjectIds)
- _fermentacao_ (ObjectId)

**Fermentação**

- _id_ (ObjectId)
- _lote_ (ObjectId)
- _dataInicio_ (date)
- _dataFim_ (date)
- _status_ (string)
- _gravidadeInicial_ (number)
- _gravidadeFinal_ (number)
- _etapaFermentacao_ (ObjectId)
- _controleFermentacao_ (ObjectId)

**EtapaFermentacao**

- _id_ (ObjectId)
- _fermentacao_ (ObjectId)
- _dataInicial_ (date)
- _dataTermino_ (date)
- _setpointTemperatura_ (number)

**ControleFermentacao**

- _id_ (ObjectId)
- _fermentacao_ (ObjectId)
- _timestamp_ ISODate()
- _setpointTemperatura_ (number)
- _temperaturaMedida_ (number)
- _situacaoRefrigeracao_ (number)

**Controlador**

- _id_ (ObjectId)
- _versaoFirmware_ (string)
- _topicoConfiguracao_ (string)
- _topicoTemperatura_ (string)
- _tempoVarredura_ (number)
