--1 Select: Seleciona os restaurantes com maior media de preco, mostrando seu respectivo shopping e nome do restaurante e media de preco
select
    s.nome as shopping,
    r.nome as restaurante,
    cast(avg(i.preco) as numeric(15,2)) as media_preco
from
    restaurante r,
    item_cardapio i,
    praca_alimentacao pa,
    espaco_rest e,
    shopping s
where
    r.cnpj = i.cnpj_rest and
    s.nome = pa.nome_shop and
    e.id_praca = pa.id and
    e.cnpj_rest = r.cnpj
group by
    s.nome,
    r.nome
order by avg(i.preco) desc

--2 Select: Espaço total de cada praça (metros quadrados) subtraido pelo total de espaço de todos os seus restaurantes
select
    t.id_praca as praca,
    (ep.metros_quadrados - t.metros_rest) as total
from
    (select
        ep.id_praca,
        sum(er.metros_quadrados) as metros_rest 
     from
         espaco_rest er,
         espaco_praca ep
     where er.id_praca = ep.id_praca
     group by ep.id_praca
     ) t,
     espaco_praca ep
where t.id_praca = ep.id_praca

--3 Select: Listar o ID das pracas de alimentação, os CNPJs dos seus restaurantes e o total de funcionarios de cada restaurante, tudo na mesma consulta
select
    p.id as id_praca_alimentacao,
    r.cnpj as cnpj_restaurante,
    count(f.id_func) as total_funcionario
from
    praca_alimentacao p,
    espaco_rest e,
    restaurante r,
    funcionario_rest f
where
    p.id = e.id_praca and
    e.cnpj_rest = r.cnpj and
    f.cnpj_rest = r.cnpj

group by rollup (p.id, r.cnpj)
order by p.id


--4 Select: Devolve a media do salario das pessoas associadas ao restaurante (Sal_funcionarios + gerente)/quantidade_funcioario + 1 gerente). Para os restaurantes que possuem gerente.
select
    t.cnpj,
    cast((t.soma+g.salario)/(t.qtd_func+1) as numeric(15,2)) as media_salario
from
    gerente g,
    (select
        count(*) as qtd_func,
        fr.cnpj_rest as cnpj,
        sum(fr.salario) as soma
    from
        funcionario_rest fr
    group by fr.cnpj_rest
    ) t
where g.cnpj_rest = t.cnpj

--5 Select: Seleciona o nome dos restaurantes que possuem a maior quantidade de Sobremesas em seu cardapio
select
    r.nome as restaurante,
    count(i.cod) as quantidade_sobremesa
from
    item_cardapio i,
    restaurante r
where
    i.categoria='Sobremesa' and
    r.cnpj = i.cnpj_rest
group by r.nome
having
    count(i.cod) = (
        select count(i.cod) as tam
        from
            item_cardapio i,
            restaurante r
	where
	    i.categoria='Sobremesa' and
	    r.cnpj = i.cnpj_rest
	group by r.nome
	order by count(i.cod) desc limit 1
    )

--6 Select: Seleciona o nome da empresa seguradora, nome do restaurante e valor do seguro, dos seguros dos restaurante do Uberladia Shopping
select
    es.nome as empresa_seguro,
    r.nome as restaurante,
    seg.valor as valor_seguro
from
    seguro seg,
    empresa_seg es,
    shopping s,
    restaurante r,
    praca_alimentacao pa,
    espaco_rest er
where
    s.nome = 'Uberlândia Shopping' and
    s.nome = pa.nome_shop and
    pa.id = er.id_praca and 
    er.cnpj_rest = r.cnpj and
    r.cnpj = seg.cnpj_rest and
    seg.cnpj_seg = es.cnpj


--7 Select: Seleciona o preco de item de cardapio mais barato de cada shopping
select
    s.nome as shopping,
    min(i.preco) as preco
from
    item_cardapio i,
    shopping s,
    restaurante r,
    praca_alimentacao pa,
    espaco_rest er
where
    pa.nome_shop = s.nome and
    r.cnpj=i.cnpj_rest and
    er.id_praca=pa.id and
    er.cnpj_rest = r.cnpj
group by s.nome
order by preco


--8 Select: Listar as principais despesas de cada restaurante que possua gerente, listando o nome do restaurante, aluguel, salarios do gerente e funcionarios, e total dessas despesas de cada restaurante
select
    r.nome as restaurante,
    sum(ep.valor_aluguel) as aluguel,
    ge.salario as salario_gerente,
    sum(f.salario) as salario_funcionarios,
    (sum(ep.valor_aluguel)+ge.salario+sum(f.salario)) as total_despesa
from
    espaco_rest ep,
    restaurante r,
    gerente ge,
    funcionario_rest f
where
    ep.cnpj_rest = r.cnpj and
    r.cnpj = ge.cnpj_rest and
    f.cnpj_rest = r.cnpj
group by r.nome,ge.salario


--9 Select: Listar o nome dos funcionarios da categoria cozinheiro, em ordem decrescente da media dos preços dos pratos que eles cozinham
select
    f.nome as cozinheiro,
    cast(avg(i.preco) as numeric(15,2)) as media_preco
from
    funcionario_rest f,
    restaurante r,
    item_cardapio i
where
    f.cnpj_rest = r.cnpj and
    r.cnpj = i.cnpj_rest and
    f.funcao = 'cozinheiro'
group by f.nome
order by media_preco desc



--10 Select: Listar para cada praca de alimentacao o numero total de mesas e cadeiras, contando com as dos restaurantes tambem, e a media de cadeiras para cada 1 mesa
select
    pa.id, (ep.n_mesa + t.mesa) as total_mesa,
    (ep.n_cad + t.cad) as total_cadeira,
    cast(cast(ep.n_cad + t.cad as float)/cast(ep.n_mesa + t.mesa as float) as numeric(3,2)) as nro_cadeira_por_mesa
from
    praca_alimentacao pa, espaco_praca ep, 
    (select pa.id as praca_id, sum(er.qtd_mesa) as mesa, sum(er.qtd_cad) as cad
	from praca_alimentacao pa, espaco_rest er	
	where pa.id = er.id_praca
	group by pa.id) t
where
    ep.id_praca = pa.id and
    t.praca_id = pa.id

--11 Select: Listar o numero de empresas que prestam serviços de cada shopping
select 
     distinct f.empresa,
     s.nome as shopping
from
    funcionario_shop f,
    shopping s
where
    s.nome = f.nome_shop
order by s.nome

--12 Select: Seleciona o nome do shopping, id da praca, valor do aluguel, metros quadrados e preco por metro quadrado de espacos de restaurante disponiveis para aluguel
select
    s.nome as shopping,
    pa.id as praca_alimentacao,
    er.valor_aluguel,
    er.metros_quadrados,
    cast(er.valor_aluguel/er.metros_quadrados as numeric(15,2)) as preco_por_metro_quad
from
    praca_alimentacao pa,
    espaco_rest er,
    shopping s
where
    pa.id = er.id_praca and
    er.cnpj_rest is null and
    s.nome = pa.nome_shop
order by
    preco_por_metro_quad