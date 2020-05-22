/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication3;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Andre
 */
class Conexao {

    Connection getConnection() {
        try {
            return DriverManager.getConnection(
                    "jdbc:mysql://localhost/cadastro", "root", "");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}

class Pessoa {

    public Pessoa() {
        this.id = 0;
        this.nome = "";
        this.email = "";
        this.logradouro = "";
        this.numero = 0;
        this.bairro = "";
        this.cidade = "";
        this.estado = "";
        this.cep = 0;
        this.escolaridade = "";
        this.boolAtivo = true;
    }

    public Pessoa(Integer id, String nome, String email, String logradouro, Integer numero, String bairro, String cidade, String estado, Integer cep, String escolaridade, Boolean boolAtivo) {
        this.id = id;
        this.nome = nome;
        this.email = email;
        this.logradouro = logradouro;
        this.numero = numero;
        this.bairro = bairro;
        this.cidade = cidade;
        this.estado = estado;
        this.cep = cep;
        this.escolaridade = escolaridade;
        this.boolAtivo = boolAtivo;
    }
    private Integer id;
    private String nome;
    private String email;
    private String logradouro;
    private Integer numero;
    private String bairro;
    private String cidade;
    private String estado;
    private Integer cep;
    private String escolaridade;
    private Boolean boolAtivo;

    public Integer getId() {
        return id;
    }

    public String getNome() {
        return nome;
    }

    public String getEmail() {
        return email;
    }

    public String getLogradouro() {
        return logradouro;
    }

    public Integer getNumero() {
        return numero;
    }

    public String getBairro() {
        return bairro;
    }

    public String getCidade() {
        return cidade;
    }

    public String getEstado() {
        return estado;
    }

    public Integer getCep() {
        return cep;
    }

    public String getEscolaridade() {
        return escolaridade;
    }

    public Boolean getBoolAtivo() {
        return boolAtivo;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setLogradouro(String logradouro) {
        this.logradouro = logradouro;
    }

    public void setNumero(Integer numero) {
        this.numero = numero;
    }

    public void setBairro(String bairro) {
        this.bairro = bairro;
    }

    public void setCidade(String cidade) {
        this.cidade = cidade;
    }

    public void setEstado(String estado) {
        this.estado = estado;
    }

    public void setCep(Integer cep) {
        this.cep = cep;
    }

    public void setEscolaridade(String escolaridade) {
        this.escolaridade = escolaridade;
    }

    public void setBoolAtivo(Boolean boolAtivo) {
        this.boolAtivo = boolAtivo;
    }

    public void imprime() {
        System.out.println(this.getId() + " " + this.getNome() + " " + this.getEmail() + " " + this.getLogradouro() + " " + this.getNumero() + " " + this.getBairro() + " " + this.getCidade() + " " + this.getEstado() + "\n");
    }
}

public class JavaApplication3 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws SQLException {
        Conexao com = new Conexao();
        Connection conexao = com.getConnection();

        StringBuilder sql = new StringBuilder("SELECT * FROM pessoa LIMIT 10");

        PreparedStatement comando = conexao.prepareStatement(sql.toString());

        ResultSet resultado = comando.executeQuery();
        Pessoa pessoa = new Pessoa();
        ArrayList<Pessoa> lista = new ArrayList<Pessoa>();
        while (resultado.next()) {

            pessoa.setId(resultado.getInt("id"));
            pessoa.setNome(resultado.getString("nome"));
            pessoa.setEmail(resultado.getString("email"));
            pessoa.setLogradouro(resultado.getString("logradouro"));
            pessoa.setNumero(resultado.getInt("numero"));
            pessoa.setBairro(resultado.getString("bairro"));
            pessoa.setCidade(resultado.getString("cidade"));
            pessoa.setEstado(resultado.getString("estado"));
            pessoa.setCep(resultado.getInt("cep"));
            pessoa.setEscolaridade(resultado.getString("escolaridade"));
            pessoa.setBoolAtivo(resultado.getBoolean("boolAtivo"));
            lista.add(pessoa);

        }
        System.out.println("\n" + " consulta 1 " + "\n");
        for (int i = 0; i < lista.size(); i++) {
            lista.get(i).imprime();
        }

////////UPDATE////////////////////////////////
        System.out.println("\n" + " atualizacao " + "\n");
        StringBuilder sql1 = new StringBuilder("UPDATE pessoa SET boolAtivo = ? WHERE boolAtivo = ? ");

        PreparedStatement comando1 = conexao.prepareStatement(sql1.toString());
        comando1.setInt(1, 0);
        comando1.setInt(2, 1);
        comando1.executeUpdate();

//////////////CONSULTA2 ////////////////////////////////////        
        System.out.println("\n" + " consulta 2 " + "\n");
        StringBuilder sql2 = new StringBuilder("SELECT * FROM pessoa WHERE id = ?");

        PreparedStatement comando2 = conexao.prepareStatement(sql2.toString());
        comando2.setInt(1, 2);
        ResultSet resultado2 = comando2.executeQuery();
        Pessoa pessoa2 = new Pessoa();
        ArrayList<Pessoa> lista2 = new ArrayList<Pessoa>();
        while (resultado2.next()) {

            pessoa2.setId(resultado2.getInt("id"));
            pessoa2.setNome(resultado2.getString("nome"));
            pessoa2.setEmail(resultado2.getString("email"));
            pessoa2.setLogradouro(resultado2.getString("logradouro"));
            pessoa2.setNumero(resultado2.getInt("numero"));
            pessoa2.setBairro(resultado2.getString("bairro"));
            pessoa2.setCidade(resultado2.getString("cidade"));
            pessoa2.setEstado(resultado2.getString("estado"));
            pessoa2.setCep(resultado2.getInt("cep"));
            pessoa2.setEscolaridade(resultado2.getString("escolaridade"));
            pessoa2.setBoolAtivo(resultado2.getBoolean("boolAtivo"));
            lista2.add(pessoa2);

        }
        for (int i = 0; i < lista2.size(); i++) {
            lista2.get(i).imprime();
        }
///////////////////consulta 3/////////////////////////////////////
            System.out.println("\n" + " consulta 3 " + "\n");
            StringBuilder sql3 = new StringBuilder("SELECT * FROM pessoa WHERE numero = ?");

            PreparedStatement comando3 = conexao.prepareStatement(sql3.toString());
            comando3.setInt(1, 43);
            ResultSet resultado3 = comando3.executeQuery();
            Pessoa pessoa3 = new Pessoa();
            ArrayList<Pessoa> lista3 = new ArrayList<Pessoa>();
            while (resultado3.next()) {
                pessoa3.setId(resultado3.getInt("id"));
                pessoa3.setNome(resultado3.getString("nome"));
                pessoa3.setEmail(resultado3.getString("email"));
                pessoa3.setLogradouro(resultado3.getString("logradouro"));
                pessoa3.setNumero(resultado3.getInt("numero"));
                pessoa3.setBairro(resultado3.getString("bairro"));
                pessoa3.setCidade(resultado3.getString("cidade"));
                pessoa3.setEstado(resultado3.getString("estado"));
                pessoa3.setCep(resultado3.getInt("cep"));
                pessoa3.setEscolaridade(resultado3.getString("escolaridade"));
                pessoa3.setBoolAtivo(resultado3.getBoolean("boolAtivo"));
                lista3.add(pessoa3);

            }
            for (int i = 0; i < lista3.size(); i++) {
                lista3.get(i).imprime();
            }
           
/////////////////////////////////////////////////////////////////////
                comando1.close();
                resultado.close();
                conexao.close();

                // TODO code application logic here
            }

        }
