import React from 'react';

const Footer = () => {
  return (
    <footer className="bg-dark text-light py-3">
      <div className="container">
        <div className="row">
          <div className="col-md-4">
            <h5>Company</h5>
            <p>Your Company Description</p>
          </div>
          <div className="col-md-4">
            <h5>Links</h5>
            <ul className="list-unstyled">
              <li>
                <a href="#">Home</a>
              </li>
              <li>
                <a href="#">Products</a>
              </li>
              <li>
                <a href="#">Contact Us</a>
              </li>
            </ul>
          </div>
          <div className="col-md-4">
            <h5>Contact</h5>
            <address>
              <p>123 Main St</p>
              <p>City, Country</p>
              <p>Email: info@example.com</p>
            </address>
          </div>
        </div>
      </div>
    </footer>
  );
};

export default Footer;