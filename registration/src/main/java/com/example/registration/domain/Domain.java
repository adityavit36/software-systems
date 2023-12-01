package com.example.registration.domain;

import com.example.registration.student.Student;
import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.ArrayList;
import java.util.List;

@Data
@Entity
@Table
@NoArgsConstructor
@AllArgsConstructor
public class Domain {
    @Id
    private Long domain_Id; // Change "id" to "studentId"
    private String program; // Change "name" to "firstName"
    private String batch; // Add "lastName" field
    private int capacity;
    @OneToMany(mappedBy = "domain", cascade = CascadeType.ALL, orphanRemoval = true)
    @JsonIgnore
    private List<Student> students = new ArrayList<>();

    public Domain(Long domain_Id, String program, String batch, int capacity) {
        this.domain_Id = domain_Id;
        this.program = program;
        this.batch = batch;
        this.capacity = capacity;
    }

}