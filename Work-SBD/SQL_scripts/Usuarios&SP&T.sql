--STORED PROCEDURED
CREATE OR REPLACE FUNCTION permission_check ()
RETURNS boolean AS $$

DECLARE
	permission boolean;
	
BEGIN
	SELECT has_table_privilege ('shopping', 'UPDATE') INTO permission; 
	
	RETURN permission; 
END $$ LANGUAGE 'plpgsql';

--TRIGGERS
create or replace function del_espaco_rest_cnpj()
returns trigger as $$
begin
    update espaco_rest set cnpj_rest=null where espaco_rest.cnpj_rest=old.cnpj;
    return old;
end $$ language 'plpgsql';

create trigger delete_espaco_rest_cnpj
before delete on restaurante
for each row execute procedure del_espaco_rest_cnpj();

--TIPO DE USUARIOS
create role postgre with superuser createdb createrole inherit noligin noreplication connection limit -1;
create role normal with nosuperuser nocreatedb nocreaterole inherit noligin noreplication connection limit -1 

grant connect on database sbd to postgre, normal;
grant usage on schema trabalho to postgre, normal;

revoke insert, update, select, delete on
	all tables in schema trabalho
	from normal;
	
grant select on
	all tables in schema trabalho
	to normal;

grant insert, update, select, delete on
	all tables in schema trabalho
	to postgre;

create role administrador with login password 'administrador';
create role usuario with login password 'senha';

grant postgre to administrador;
grant normal to usuario;
