import React, { useState ,useEffect} from 'react';
import 'bootstrap/dist/css/bootstrap.min.css'; // Import Bootstrap styles

const StudentForm = () => {
    const [student, setStudent] = useState({
        firstName: '',
        lastName: '',
        email: '',
        photographPath: '',
    });
    const [domains, setDomains] = useState([]); // State to store available domains
    const [selectedDomainId, setSelectedDomainId] = useState(0);
    useEffect(() => { // Fetch the list of domains when the component mounts
        fetch('http://localhost:8080/api/students/domains')
            .then((response) => response.json())
            .then((data) =>{ setDomains(data);setSelectedDomainId(data[0].domain_Id);})
            .catch((error) => console.error('Error fetching domains:', error));
    }, []);

    const handleChange = (e) => {
        const { name, value, type } = e.target;
        // if (name === 'domain') {
        //     const selectedDomain = domains.find((domain) => domain.program === value);
        //     setSelectedDomainId(selectedDomain ? selectedDomain.domainId : null);
        // }
        setStudent((prevStudent) => ({
            ...prevStudent,
            [name]: type === 'file' ? e.target.files[0] : value,
        }));
    };
    const handleSubmit = async (e) => {
        e.preventDefault();
        console.log(selectedDomainId);
        console.log("Form data - ",e);
        try {
            const response = await fetch('http://localhost:8080/api/students/add', {
                method: 'POST',
                body:JSON.stringify ({
                    'firstName': student.firstName,
                    'lastName': student.lastName,
                    'email': student.email,
                    'domain': domains.find(d=>d.domain_Id==selectedDomainId),
                    'graduationYear': student.graduationYear,
                    'photographPath': student.photographPath
                }),
                headers:{
                    'Content-type':'application/json;charset=UTF-8'
                }
            });

            if (response.ok) {
                const savedStudent = await response.json();
                console.log('Student added:', savedStudent);
            } else {
                console.error('Failed to add student');
            }
        } catch (error) {
            console.error('Error:', error);
        }
    };
    return (
        <form onSubmit={handleSubmit} className="container mt-4">
            <div className="mb-3">
                <label className="form-label">firstName</label>
                <input type="text" className="form-control" name="firstName" value={student.firstName} onChange={handleChange} />
            </div>
            <div className="mb-3">
                <label className="form-label">lastName</label>
                <input type="text" className="form-control" name="lastName" value={student.lastName} onChange={handleChange} />
            </div>
            <div className="mb-3">
                <label className="form-label">email</label>
                <input type="text" className="form-control" name="email" value={student.email}onChange={handleChange}  />
            </div>
            <div className="mb-3">
                <label className="form-label">graduationYear</label>
                <input type="number" className="form-control" name="graduationYear" value={student.graduationYear}onChange={handleChange}  />
            </div>
            <div className="mb-3">
                <label className="form-label">domain</label>
                <select className="form-select" name="domain" value={selectedDomainId}onChange={e=>setSelectedDomainId(e.target.value)} >
                    {
                        domains.map((d)=>{
                            return (
                                <option key = {d.domain_Id} value = {d.domain_Id}>
                                {d.program+d.batch}
                                </option>);
                        })
                    }
                    {/* <option value="M.Tech CSE">M.Tech CSE</option>
                    <option value="M.Tech ECE">M.Tech ECE</option>
                    <option value="IM.Tech CSE">IMtech CSE</option>
                    <option value="IM.Tech ECE">IMtech ECE</option>
                    <option value="Phd CSE">IMtech CSE</option>
                    <option value="Phd ECE">IMtech ECE</option> */}
                </select>
            </div>
            <div className="mb-3">
                <label className="form-label">photographPath</label>
                {/* <input type="text" className="form-control" name="photographPath" value={student.photographPath} onChange={handleChange}/> */}
                <input type="text" className="form-control" name="photographPath" onChange={handleChange}/>
            </div>
            <button type="submit" className="btn btn-primary">
                Submit
            </button>
        </form>
    );
};

export default StudentForm;