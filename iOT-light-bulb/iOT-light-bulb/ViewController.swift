//
//  ViewController.swift
//  iOT-light-bulb
//
//  Created by Johnson Lai on 13/05/2017.
//  Copyright © 2017 johnsonlwh7. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

    }
    @IBAction func onBtnPressed(_ sender: Any) {
        if let url = URL(string: "http://192.168.0.2/LED=ON") {
            UIApplication.shared.open(url, options: [:]) {
                boolean in
                // do something with the boolean
            }
        }
    }
    @IBAction func offBtnPressed(_ sender: Any) {
    }
    
}

