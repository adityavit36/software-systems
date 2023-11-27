package com.example.registration.student;

import com.example.registration.domain.Domain;
import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Table
@NoArgsConstructor
@AllArgsConstructor
@Data
public class Student {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long studentId; // Change "id" to "studentId"
    private String firstName; // Change "name" to "firstName"
    private String lastName; // Add "lastName" field
    private String email;
    private String photographPath; // Change "photoUrl" to "photographPath"
    private Integer graduationYear; // Change to Integer for the graduation year
    private String rollNumber;
    @ManyToOne
    @JoinColumn(name = "domain_id", nullable = false)
    private Domain domain;
}
