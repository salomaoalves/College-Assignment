data ClienteQChega = Nao | Sim TempoQChegou TempoPAtend
    deriving(Show,Eq)
data ClienteQSai = Nenhum |Liberado TempoQChegou TempoDEsp TempoPAtend
    deriving(Show,Eq)

type TempoQChegou = Int
type TempoPAtend = Int
type TempoDEsp = Int
type Tempo = Int
type Fila = [Int]

-------------------------------------Estado Da Fila-----------------------------------

type EstadoDaFila = (Tempo, TempoDeAtend,[ClienteQChega])

adicionaCliente:: ClienteQChega -> EstadoDaFila -> EstadoDaFila
adicionaCliente m (tempo,tempDeAtend,ml) = (tempo,tempDeAtend, ml++[m])

processaFila :: EstadoDaFila -> (EstadoDaFila, [ClienteQSai])
processaFila (tempo,tempDeAtend,[]) = ((tempo+1,tempDeAtend,[]),[])
processaFila (tempo,tempDeAtend,(Sim a tempNecDAtend:resto))
    |tempDeAtend < tempNecDAtend = ((tempo+1),(tempDeAtend+1),((Sim a tempNecDAtend:resto),[]))
    |otherwise = ((tempo+1,0,resto),[Liberado a (tempo-tempNecDAtend-a) tempNecDAtend])

filaDeInicio :: EstadodaFila
filaDeInicio = (0,0,[])

tamanhoDaFila :: EstadoDaFila -> Int
tamanhoDaFila (tempo,tempoDeAtend,l) = length l

filaVazia :: EstadoDaFila -> Bool
filaVazia (t,s,q) = (q == [])

------------------------------Estado Do Servidor-------------------------------------

type EstadoDoServirdor = [EstadoDaFila]

colocaNaFila :: Int -> ClienteQChega -> EstadoDoServidor -> EstadoDoServidor
colocaNaFila  n im st = take n st ++ [novoEstadoDaFila] ++ drop (n+1) st
    where 
    	novoEstadoDaFila = adicionaCliente im (st!!n)

processaServidor :: EstadoDoServidor -> (EstadoDoServidor, [ClienteQSai])
processaServidor [] = ([],[])
processaServidor (q:qs) = ((nq:nqs), mess ++ messes)
    where
        (nq,mess) = processaFila q
        (nqs,messes) = processaServidor qs

processaSimulacao :: EstadoDoServidor -> ClienteQChega -> (EstadoDoServidor,[ClienteQSai])
processaSimulacao estServ im = (adicionaNovoObjeto im estServ1,clientQSai)
    where
        (estServ1,clientQSai) = processaServidor estServ

adicionaNovoObjeto :: ClienteQChega -> EstadoDoServidor -> EstadoDoServidor
adicionaNovoObjeto Nao estServ = estServ
adicionaNovoObjeto (Sim tempoDeChegada tempoNecAtend) estServ = colocaNaFila (menorFila estServ) (Sim tempoDeChegada tempoNecAtend) estServ

estadoInicialDoServidor :: EstadoDoServidor
estadoInicialDoServidor = copy nroDeFilas filaDeInicio

tamanhoDoServidor :: EstadoDoServidor -> Int
tamanhoDoServidor = length

menorFila :: EstadoDoServidor -> Int
menorFila [q] = 0
menorFila (q:qs)
    |tamanhoDaFila (qs!!menor) <= tamanhoDaFila q = menor + 1
    |otherwise = 0
    where
        menor = menorFila qs

-------------------------------Números pseudoaleatorios---------------------------

semente :: Int
semente = 17489

multiplicador :: Int
multiplicador = 25173

incremento :: Int
incremento = 13849

modulo :: Int
modulo = 65536

dist :: Num t => [(t, Float)]
dist = [(1, 0.2), (2, 0.25), (3, 0.25), (4, 0.15), (5, 0.1), (6, 0.05)]

proxNumAleat :: Int -> Int
proxNumAleat n = (multiplicador*n + incremento) rem modulo

seqAleatoria :: (Int -> [Int])
seqAleatoria = iterate proxNumAleat

escalaSequencia :: Int -> Int -> ([Int] -> [Int])
escalaSequencia a b = map scala
    where
        scala n = n/denom + a
        faixa = b – a + 1
        denom = modulo/faixa

geraFuncao :: [(t,Float)] -> (Float -> t)
geraFuncao = geraFun dist 0.0
geraFun ((ob,p):dist) nUlt aleat
    |nProx >= aleat && aleat > nUlt = ob
    |otherwise = geraFun dist nProx aleat
    where
        nProx = p* fromInteger modulo + nUlt

--------------------------------Simulação---------------------------------------

simule :: EstadoDoServidor [ClienteQChega] -> [ClienteQSai]
simule estDoServ (im:messes) = outmesses ++ simule proxEstDoServ messes
    where
        (proxEstDoServ,outmesses) = processaSimulacao estDoServ im 

processaSimulacao :: EstadoDoServidor ClienteQChega -> (EstadoDoServidor, [ClienteQSai])

seqDeTempos :: [TempoPAtend]
seqDeTempos = map (geraFuncao dist.fromInteger) (seqAleatoria semente)

entradaDaSimulacao :: [ClienteQChega]
entradaDaSimulacao = zipWith Sim [ 1..] 

seqDeTempos = [Sim 1 2, Sim 2 5, Sim 3 1, …

simule estadoInicialDoServidor entradaDaSimulacao = [Liberado 1 0 2, Liberado 3 0 1, Liberado 6 0 1, Liberado 2 0 5, Liberado 5 0 3, Liberado 4 0 4, Liberado 7 2 2, …

entradaDaSimulacao2 :: [ClienteQChega]
entradaDaSimulacao2 = take 50 
entradaDaSimulacao ++ naos 

zipWith f (a:x) (b:y) = ((f a b) : zipWith f x y)
zipWith _ _ _ = []

naos :: [ClienteQChega]
naos = (Nao:naos)

tempoDeEsperaTotal :: ([ClienteQSai] -> Int)
tempoDeEsperaTotal = sum . map tempoDEsp
    where
	    tempoDEsp (Liberado _ w _) = w
