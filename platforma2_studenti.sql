-- MySQL dump 10.13  Distrib 8.0.30, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: platforma2
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `studenti`
--

DROP TABLE IF EXISTS `studenti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `studenti` (
  `id_student` int NOT NULL,
  `an` int DEFAULT NULL,
  `nr_ore` int DEFAULT NULL,
  KEY `id_student_idx` (`id_student`),
  CONSTRAINT `studenti_ibfk_1` FOREIGN KEY (`id_student`) REFERENCES `users` (`id_user`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `studenti`
--

LOCK TABLES `studenti` WRITE;
/*!40000 ALTER TABLE `studenti` DISABLE KEYS */;
INSERT INTO `studenti` VALUES (1,1,34),(2,1,34),(3,1,34),(4,1,34),(5,1,34),(6,1,34),(7,1,34),(8,1,34),(9,1,34),(10,1,34),(11,1,34),(12,1,34),(13,1,34),(14,1,34),(15,1,34),(16,1,34),(17,1,34),(18,1,34),(19,1,34),(20,1,34),(21,1,34),(22,1,34),(23,1,34),(24,1,34),(25,1,34),(26,1,34),(27,1,34),(28,1,34),(29,1,34),(30,1,34),(47,1,34),(48,1,34),(49,1,34),(50,1,34),(51,1,34),(52,1,34),(53,1,34),(54,1,34),(55,1,34),(56,1,34),(57,1,34),(58,1,34),(59,1,34),(60,1,34),(61,1,34),(62,1,34),(63,1,34),(64,1,34),(65,1,34),(66,1,34),(67,1,34),(68,1,34),(69,1,34),(70,1,34),(71,1,34),(72,1,34),(73,1,34),(74,1,34),(75,1,34),(76,1,34);
/*!40000 ALTER TABLE `studenti` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-01-19  2:08:24
