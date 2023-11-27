package com.example.registration.student;

import com.example.registration.domain.Domain;
import com.example.registration.domain.DomainRepository;
import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.List;

@Configuration
public class StudentConfig {
    @Bean
    CommandLineRunner commandLineRunner(DomainRepository domainRepository, StudentRepository studentRepository){
        return args->{
            Domain d1 = new Domain(1L,"MTech","CSE",60);
            Domain d2 = new Domain(2L,"MTech","ECE",60);
            Domain d3 = new Domain(3L,"IMTech","CSE",60);
            Domain d4 = new Domain(4L,"IMTech","ECE",60);
            Domain d5 = new Domain(5L,"Phd","CSE",60);
            Domain d6 = new Domain(6L,"Phd","ECE",60);
            Domain d7 = new Domain(7L,"MS","CSE",60);
            Domain d8 = new Domain(8L,"MS","ECE",60);
            domainRepository.saveAll(List.of(d1,d2,d3,d4,d5,d6,d7,d8));
            Student s1 = new Student(1L,"Aditya","Sharma","aditya@gmail.com","www.lorempicsum.com",2025,"MT2023021",d1);
            Student s2 = new Student(2L,"Abhinav","Dhoka","abhinav@gmail.com","www.lorempicsum.com",2025,"MT2023062",d2);
            studentRepository.saveAll(List.of(s1,s2));
        };
    }
}
