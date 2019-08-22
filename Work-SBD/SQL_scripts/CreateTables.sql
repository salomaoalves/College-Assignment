create schema trabalho;
set search_path to trabalho;

create table shopping(
    nome varchar(50) not null,
    endereco varchar(50),
    telefone varchar(20),
    constraint nomepk primary key (nome)
);

create table praca_alimentacao(
    id integer not null,
    nome_shop varchar(50) not null,
    constraint idppk primary key (id),
    constraint nome_shopfk foreign key (nome_shop)
        references shopping(nome)
        on update cascade
        on delete cascade
);

create table funcionario_shop(
    id varchar(11) not null,
    empresa varchar(50) not null,
    nome varchar(50) not null,
    setor varchar(50),
    nome_shop varchar(50),
    constraint idfpk primary key (id),
    constraint nome_shopfk foreign key (nome_shop)
        references shopping(nome)
        on update cascade
        on delete cascade
);

create table espaco_praca(
    id_praca integer not null,
    metros_quadrados float,
    n_cad integer,
    n_mesa integer,
    constraint idpk primary key (id_praca),
    constraint idfk foreign key (id_praca)
        references praca_alimentacao(id)
        on update cascade
        on delete cascade
);

create table dono(
    cpf varchar(11) not null,
    nome varchar(50),
    telefone varchar(20),
    lucro_trimestral float,
    constraint dcpfpk primary key (cpf)
);

create table restaurante(
    cnpj varchar(20) not null,
    categoria varchar(50),
    nome varchar(50),
    cpf_dono varchar(11) not null,
    constraint rcnpjpk primary key (cnpj),
    constraint cpf_donofk foreign key (cpf_dono)
        references dono(cpf)
        on update cascade
        on delete cascade
);

create table espaco_rest(
    cod_espaco integer not null,
	cnpj_rest varchar(20),
	id_praca integer not null,
    metros_quadrados float,
    qtd_cad integer,
    qtd_mesa integer,
	valor_aluguel float,
    constraint cod_espacopk primary key (cod_espaco),
	constraint erid_pracafk foreign key (id_praca)
	    references praca_alimentacao(id)
		on update cascade
		on delete cascade,
	constraint er_cnpjrestfk foreign key (cnpj_rest)
	    references restaurante(cnpj)
);

create table empresa_seg(
    cnpj varchar(20) not null,
    nome varchar(50),
    telefone varchar(20),
    constraint ecnpjpk primary key (cnpj)
);

create table seguro(
    cod integer not null,
    valor float,
    cnpj_rest varchar(20) not null,
    cnpj_seg varchar(20) not null,
    constraint codpk primary key (cod),
    constraint cnpj_restfk foreign key (cnpj_rest)
        references restaurante (cnpj)
        on update cascade
        on delete cascade,
    constraint cnpj_segfk foreign key (cnpj_seg)
        references empresa_seg (cnpj)
        on update cascade
        on delete cascade
);

create table funcionario_rest(
    id_func varchar(20) not null,
    salario float,
	funcao varchar(50),
    nome varchar(50),
    telefone varchar(20),
    cnpj_rest varchar(20) not null,
	check (salario>=0),
    constraint id_funcpk primary key (id_func),
    constraint cnpj_restfk foreign key (cnpj_rest)
        references restaurante (cnpj)
        on update cascade
        on delete cascade
);


create table gerente(
    cpf varchar(11) not null,
    salario float,
    nome varchar(50),
    telefone varchar(20),
    cnpj_rest varchar(20),
	check (salario>=0),
    constraint gcpfpk primary key (cpf),
    constraint cnpj_restfk foreign key (cnpj_rest)
        references restaurante (cnpj)
        on update cascade
        on delete cascade
);

create table item_cardapio(
    cod integer not null,
	cnpj_rest varchar(20),
    categoria varchar(50),
	preco float,
	nome varchar(50),
	check(preco>0),
    constraint n_pedidopk primary key (cod),
	constraint icarcnpjfk foreign key (cnpj_rest)
        references restaurante (cnpj)
        on update cascade
        on delete cascade
	
);