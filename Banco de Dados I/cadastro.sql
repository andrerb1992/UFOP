-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: 16-Mar-2017 às 18:12
-- Versão do servidor: 10.1.19-MariaDB
-- PHP Version: 5.6.28

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cadastro`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `aluno`
--

CREATE TABLE `aluno` (
  `data_inscricao` date NOT NULL,
  `idPessoa` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `aluno`
--

INSERT INTO `aluno` (`data_inscricao`, `idPessoa`) VALUES
('2017-03-29', 10),
('2017-03-17', 30);

-- --------------------------------------------------------

--
-- Estrutura da tabela `curso`
--

CREATE TABLE `curso` (
  `id` int(11) UNSIGNED NOT NULL,
  `data_criacao` date NOT NULL,
  `descricao` text NOT NULL,
  `informacoes` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `curso`
--

INSERT INTO `curso` (`id`, `data_criacao`, `descricao`, `informacoes`) VALUES
(1, '2017-03-22', 'curso de ciencia', 'aulas aos sabados'),
(10, '2017-03-28', 'nenhuma', 'nenhuma');

-- --------------------------------------------------------

--
-- Estrutura da tabela `diario`
--

CREATE TABLE `diario` (
  `data` date NOT NULL,
  `idTurma` int(11) UNSIGNED NOT NULL,
  `atividades` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estrutura da tabela `estudante`
--

CREATE TABLE `estudante` (
  `idPessoa` int(11) NOT NULL,
  `nomeResponsavel` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `estudante`
--

INSERT INTO `estudante` (`idPessoa`, `nomeResponsavel`) VALUES
(10, 'andre'),
(30, 'andre');

-- --------------------------------------------------------

--
-- Estrutura da tabela `funcionario`
--

CREATE TABLE `funcionario` (
  `idPessoa` int(11) NOT NULL,
  `inicio` int(11) UNSIGNED NOT NULL,
  `final` int(11) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estrutura da tabela `instrutor`
--

CREATE TABLE `instrutor` (
  `idPessoa` int(11) NOT NULL,
  `inicio` int(11) UNSIGNED NOT NULL,
  `fim` int(11) UNSIGNED NOT NULL,
  `cargaHoraria` int(11) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `instrutor`
--

INSERT INTO `instrutor` (`idPessoa`, `inicio`, `fim`, `cargaHoraria`) VALUES
(50, 20, 22, 20);

-- --------------------------------------------------------

--
-- Estrutura da tabela `local`
--

CREATE TABLE `local` (
  `id` int(11) UNSIGNED NOT NULL,
  `responsavel` varchar(50) NOT NULL,
  `descricao` text NOT NULL,
  `logradouro` varchar(50) NOT NULL,
  `numero` int(11) UNSIGNED NOT NULL,
  `bairro` varchar(50) NOT NULL,
  `cidade` varchar(50) NOT NULL,
  `estado` varchar(50) NOT NULL,
  `CEP` int(11) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `local`
--

INSERT INTO `local` (`id`, `responsavel`, `descricao`, `logradouro`, `numero`, `bairro`, `cidade`, `estado`, `CEP`) VALUES
(30, 'carlos', 'nenhuma', 'rua cinco', 133, 'centro', 'belo horizonte', 'mg', 35400);

-- --------------------------------------------------------

--
-- Estrutura da tabela `matriculado`
--

CREATE TABLE `matriculado` (
  `dataMatricula` date NOT NULL,
  `idTurma` int(11) NOT NULL,
  `idPessoa` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `matriculado`
--

INSERT INTO `matriculado` (`dataMatricula`, `idTurma`, `idPessoa`) VALUES
('2017-03-22', 22, 30);

-- --------------------------------------------------------

--
-- Estrutura da tabela `pessoa`
--

CREATE TABLE `pessoa` (
  `id` int(11) NOT NULL,
  `nome` varchar(50) NOT NULL,
  `email` varchar(50) NOT NULL,
  `logradouro` varchar(20) NOT NULL,
  `numero` int(11) UNSIGNED NOT NULL,
  `bairro` varchar(20) NOT NULL,
  `cidade` varchar(20) NOT NULL,
  `estado` varchar(20) NOT NULL,
  `CEP` int(11) UNSIGNED NOT NULL,
  `escolaridade` varchar(20) NOT NULL,
  `boolAtivo` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `pessoa`
--

INSERT INTO `pessoa` (`id`, `nome`, `email`, `logradouro`, `numero`, `bairro`, `cidade`, `estado`, `CEP`, `escolaridade`, `boolAtivo`) VALUES
(2, 'rafael', 'rbrito@gmail.com', 'av caue', 88, 'campestre', 'itabira', 'mg', 35900, 'ensino medio', 0),
(10, 'andre', 'andrerb@gmail.com', 'artur vitorino', 612, 'bauxita', 'ouro preto', 'mg', 35400, '35400', 0),
(12, 'fred', 'fred@ggs.afa', 'av jk', 123, 'centro', 'belo horizonte', 'sp', 34111, 'ensino medio', 0),
(20, 'joao', 'da@gmail.com', 'rua um', 43, 'bauxita', 'ouro preto', 'mg', 35400, 'graduação', 0),
(22, 'joao', 'andre@gmail', 'artur queiroz', 311, 'alvorada', 'itabira', 'mg', 354000, 'fundamental', 0),
(30, 'jose', 'fj@gmaiil.com', 'rua dois ', 98, 'centro', 'itabira', 'mg', 35600, 'fundamental', 0),
(44, 'andrews', 'andr@gmail.com', 'rua tres', 44, 'nova luz', 'oriente', 'mt', 31000, 'ensino medio', 0),
(50, 'paulo', 'p@gmail.com', 'rua brasil', 43, 'centro', 'ouro preto', 'mg', 35400, 'ensino medio', 0),
(55, 'anf', 'dadap', 'daaaa', 43, 'dce', 'cmo', 'sp', 32110, 'medio', 0),
(63, 'lari', 'lari@gmail.com', 'rua norte', 23, 'vila madalena', 'ouro preto', 'mg', 35400, 'graduação', 0),
(98, 'jaja', 'jja@faljfa.com', 'rua dez', 443, 'vila aparecida', 'belo vale', 'mg', 32111, 'fundamental', 0);

-- --------------------------------------------------------

--
-- Estrutura da tabela `responde`
--

CREATE TABLE `responde` (
  `boolPresente` tinyint(1) NOT NULL,
  `idPessoa` int(11) NOT NULL,
  `idTurma` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `responde`
--

INSERT INTO `responde` (`boolPresente`, `idPessoa`, `idTurma`) VALUES
(1, 10, 22);

-- --------------------------------------------------------

--
-- Estrutura da tabela `responsavel`
--

CREATE TABLE `responsavel` (
  `nome` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `responsavel`
--

INSERT INTO `responsavel` (`nome`) VALUES
('carlos');

-- --------------------------------------------------------

--
-- Estrutura da tabela `telefonelocal`
--

CREATE TABLE `telefonelocal` (
  `telefone` int(11) UNSIGNED NOT NULL,
  `idLocal` int(11) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `telefonelocal`
--

INSERT INTO `telefonelocal` (`telefone`, `idLocal`) VALUES
(44429987, 30);

-- --------------------------------------------------------

--
-- Estrutura da tabela `telefonepessoa`
--

CREATE TABLE `telefonepessoa` (
  `telefone` int(11) UNSIGNED NOT NULL,
  `idPessoa` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `telefonepessoa`
--

INSERT INTO `telefonepessoa` (`telefone`, `idPessoa`) VALUES
(22342233, 20);

-- --------------------------------------------------------

--
-- Estrutura da tabela `telefoneresponsavel`
--

CREATE TABLE `telefoneresponsavel` (
  `telefone` int(11) UNSIGNED NOT NULL,
  `nomeResponsavel` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estrutura da tabela `turma`
--

CREATE TABLE `turma` (
  `id` int(11) UNSIGNED NOT NULL,
  `horario` int(11) UNSIGNED NOT NULL,
  `dataInicio` date NOT NULL,
  `dataTermino` date NOT NULL,
  `idCurso` int(11) UNSIGNED NOT NULL,
  `idLocal` int(11) UNSIGNED NOT NULL,
  `idPessoa` int(11) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `turma`
--

INSERT INTO `turma` (`id`, `horario`, `dataInicio`, `dataTermino`, `idCurso`, `idLocal`, `idPessoa`) VALUES
(20, 11, '2017-03-21', '2017-05-18', 43, 23, 20);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `aluno`
--
ALTER TABLE `aluno`
  ADD PRIMARY KEY (`idPessoa`);

--
-- Indexes for table `curso`
--
ALTER TABLE `curso`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `diario`
--
ALTER TABLE `diario`
  ADD PRIMARY KEY (`data`),
  ADD KEY `idTurma` (`idTurma`);

--
-- Indexes for table `estudante`
--
ALTER TABLE `estudante`
  ADD PRIMARY KEY (`idPessoa`);

--
-- Indexes for table `funcionario`
--
ALTER TABLE `funcionario`
  ADD PRIMARY KEY (`idPessoa`);

--
-- Indexes for table `instrutor`
--
ALTER TABLE `instrutor`
  ADD PRIMARY KEY (`idPessoa`);

--
-- Indexes for table `local`
--
ALTER TABLE `local`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `matriculado`
--
ALTER TABLE `matriculado`
  ADD PRIMARY KEY (`idPessoa`);

--
-- Indexes for table `pessoa`
--
ALTER TABLE `pessoa`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `responde`
--
ALTER TABLE `responde`
  ADD PRIMARY KEY (`idPessoa`);

--
-- Indexes for table `responsavel`
--
ALTER TABLE `responsavel`
  ADD PRIMARY KEY (`nome`);

--
-- Indexes for table `telefonelocal`
--
ALTER TABLE `telefonelocal`
  ADD PRIMARY KEY (`telefone`),
  ADD KEY `idLocal` (`idLocal`);

--
-- Indexes for table `telefonepessoa`
--
ALTER TABLE `telefonepessoa`
  ADD PRIMARY KEY (`idPessoa`);

--
-- Indexes for table `telefoneresponsavel`
--
ALTER TABLE `telefoneresponsavel`
  ADD PRIMARY KEY (`nomeResponsavel`);

--
-- Indexes for table `turma`
--
ALTER TABLE `turma`
  ADD PRIMARY KEY (`id`);

--
-- Constraints for dumped tables
--

--
-- Limitadores para a tabela `aluno`
--
ALTER TABLE `aluno`
  ADD CONSTRAINT `aluno_fgk_idPessoa` FOREIGN KEY (`idPessoa`) REFERENCES `pessoa` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limitadores para a tabela `diario`
--
ALTER TABLE `diario`
  ADD CONSTRAINT `idTurma_fgk_idTurma` FOREIGN KEY (`idTurma`) REFERENCES `turma` (`id`);

--
-- Limitadores para a tabela `estudante`
--
ALTER TABLE `estudante`
  ADD CONSTRAINT `estudante_fgk_idPessoa` FOREIGN KEY (`idPessoa`) REFERENCES `aluno` (`idPessoa`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Limitadores para a tabela `funcionario`
--
ALTER TABLE `funcionario`
  ADD CONSTRAINT `funcionario_fgk_idPessoa` FOREIGN KEY (`idPessoa`) REFERENCES `aluno` (`idPessoa`) ON UPDATE CASCADE;

--
-- Limitadores para a tabela `instrutor`
--
ALTER TABLE `instrutor`
  ADD CONSTRAINT `instrutor_fgk_idPessoa` FOREIGN KEY (`idPessoa`) REFERENCES `pessoa` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limitadores para a tabela `matriculado`
--
ALTER TABLE `matriculado`
  ADD CONSTRAINT `matriculado_fgk_idPessoa` FOREIGN KEY (`idPessoa`) REFERENCES `aluno` (`idPessoa`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limitadores para a tabela `responde`
--
ALTER TABLE `responde`
  ADD CONSTRAINT `responde_fgk_idPessoa` FOREIGN KEY (`idPessoa`) REFERENCES `aluno` (`idPessoa`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limitadores para a tabela `telefonelocal`
--
ALTER TABLE `telefonelocal`
  ADD CONSTRAINT `idLocal_fgk_idLocal` FOREIGN KEY (`idLocal`) REFERENCES `local` (`id`);

--
-- Limitadores para a tabela `telefonepessoa`
--
ALTER TABLE `telefonepessoa`
  ADD CONSTRAINT `pessoa_fgk_idPessoa` FOREIGN KEY (`idPessoa`) REFERENCES `pessoa` (`id`) ON UPDATE CASCADE;

--
-- Limitadores para a tabela `telefoneresponsavel`
--
ALTER TABLE `telefoneresponsavel`
  ADD CONSTRAINT `telefoneresponsavel_fgk_nomeResponsavel` FOREIGN KEY (`nomeResponsavel`) REFERENCES `responsavel` (`nome`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
