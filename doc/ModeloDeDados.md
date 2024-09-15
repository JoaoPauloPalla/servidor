# Modelo de Dados do sistema

Serão consideradas as collections:

## Usuário

- id: ObjectId
- nome: string
- email: string
- senha: string
- tipo: string
- dataCadastro: date
- validadeToken: date

## Receita

- id: ObjectId
- nome: string
- tipo: string
- descricao: string
- tempoFermentacao: number
- tempoMaturacao: number
- ingredientes: array of objects
- usuario: ObjectId
- dataCadastro: date
- dataAtualizacao: date

## Estoque

- id: ObjectId
- nome: string
- tipo: string
- quantidade: number
- unidadeMedida: string

## Lote

- id: ObjectId
- numeroLote: number
- dataInicioProducao: date
- dataTerminoProducao: date
- receita: ObjectId
- quantidadeProduzida: number
- situacao: string
- fermentacao: ObjectId

## Fermentação

- id: ObjectId
- lote: ObjectId
- dataInicio: date
- dataFim: date
- situacao: string
- gravidadeInicial: number
- gravidadeFinal: number
- etapaFermentacao: ObjectId
- controleFermentacao: ObjectId
- medicaoGravidade: array

## Historico Gravidade

- id: ObjectId
- dataMedida: date
- gravidade: number

## EtapaFermentacao

- id: ObjectId
- fermentacao: ObjectId
- dataInicial: date
- dataTermino: date
- setpointTemperatura: number

## ControleFermentacao

- id: ObjectId
- fermentacao: ObjectId
- timestamp: ISODate
- setpointTemperatura: number
- temperaturaMedida: number
- situacaoRefrigeracao: number

## Controlador

- id: ObjectId
- versaoFirmware: string
- topicoConfiguracao: string
- tempoVarredura: number
