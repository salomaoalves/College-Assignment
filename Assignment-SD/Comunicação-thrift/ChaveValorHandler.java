package chavevalor;

import org.apache.thrift.TException;
import java.util.HashMap;
import chavevalor.*;

public class ChaveValorHandler implements ChaveValor.Iface {
    private HashMap<Integer,String> kv = new HashMap<>();
    @Override
    public String getKV(int key) throws TException {
        if(kv.containsKey(key))
            return kv.get(key);
       else
            throw new KeyNotFound();
    }

    @Override
    public String setKV(int key, String valor) throws TException {

        // busca o valor antigo e seta o novo
        String valorAntigo = kv.getKV(key);
        kv.put(key,valor);
        
        // caso NÃO tenha valor antigo, retorna que não tem
        // caso tenha, retorne o valor antigo
        if (valorAntigo){
            return "Não existe valor anterior";
        }else{
            return valorAntigo;
        }       
    }

    @Override
    public void delKV(int key) throws TException {
        kv.remove(key);
    }    
}