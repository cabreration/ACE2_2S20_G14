import { Component, OnInit, ViewChild, ElementRef } from '@angular/core';
import { APIDataService } from '../apidata.service';

@Component({
  selector: 'app-registry',
  templateUrl: './registry.component.html',
  styleUrls: ['./registry.component.css']
})

export class RegistryComponent implements OnInit {

  name: string = null;
  dpi: string = null;
  photo = null;
  imgSrc: string;
  selectedImage: any = null;

  @ViewChild('photoInput') photoInput: ElementRef;

  constructor(private api: APIDataService) { }

  ngOnInit(): void {
  }

  sendRecord() {
    if (this.name == null || this.name == '') {
      alert('Debe ingresar su nombre!');
      return;
    }
    else if (this.dpi == null || this.dpi == '') {
      alert('Debe ingresar su numero de dpi!');
    }

    let user = {
      nombre: this.name,
      dpi: Number(this.dpi),
      base64: this.photo
    }

    let observer = this.api.PostRequest('/UserInfo', user).subscribe(res => {
      console.log(res);
      observer.unsubscribe();
    })

    this.name = '';
    this.dpi= '';
  }

  takePhoto() {
    this.photoInput.nativeElement.click();
  }

  loadPhoto(event: any) {
    if (event.target.files && event.target.files[0]) {
      const reader = new FileReader();

      reader.onload = (e: any) => this.imgSrc = e.target.result;
      reader.readAsDataURL(event.target.files[0]);
      this.selectedImage = reader;

      setTimeout(() => this.trimPhoto(), 3000)
    }
  }

  trimPhoto(): void {
    if (this.selectedImage == null) return;
    
    let str = this.selectedImage.result;
    let start = 0;
    for (let i = 0; i < str.length; i++) {
      if (str.charAt(i) == ',') {
        start = i;
        break;
      }
    }
    start++;
    let str2 = str.substr(start, str.length - start)
    this.photo = str2;
    console.log(this.photo)
  }
}
