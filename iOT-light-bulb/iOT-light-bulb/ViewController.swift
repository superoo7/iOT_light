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
        let url = URL(string: "http://192.168.0.2/LED=ON")
        
        let onTask = URLSession.shared.dataTask(with: url!) {(data, response, error) in
            print(NSString(data: data!, encoding: String.Encoding.utf8.rawValue)!)
        }
        onTask.resume()
    }
    @IBAction func offBtnPressed(_ sender: Any) {
        let url = URL(string: "http://192.168.0.2/LED=OFF")
        
        let offTask = URLSession.shared.dataTask(with: url!) {(data, response, error) in
            print(NSString(data: data!, encoding: String.Encoding.utf8.rawValue)!)
        }
        
        offTask.resume()
    }
    
}

